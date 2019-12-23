#include <cstdlib>
#include <algorithm>
#include "../../include/algorithm/SchedulingProblem.hpp"
#include "../../include/lessonplan/LessonplanIndividualFactory.hpp"
#include "../../include/lessonplan/LessonplanScoreList.hpp"

namespace lessonplans {

    LessonplanIndividual* SchedulingProblem::getSampleLessonplan(){
        LessonplanIndividual* lessonplanIndividual = LessonplanIndividualFactory::createLessonplanIndividual(this->schedulingProblemProperties);

        return lessonplanIndividual;
    }

    LessonplanIndividual* SchedulingProblem::getSampleLessonplanGreedly(){
        LessonplanIndividual* lessonplanIndividual = LessonplanIndividualFactory::createLessonplanIndividualGreedly(this->schedulingProblemProperties);

        return lessonplanIndividual;
    }

    vector<vector<int>> SchedulingProblem::evaluateLessonplan(LessonplanIndividual* lessonplanIndividual) {
        unsigned short invalidClassSubjectSameLessonsTimes = this->checkClassesSubjectsWithSameTimesLessons(lessonplanIndividual);

        unsigned short invalidTeacherSameLessonsTimes = this->checkTeachersWithSameTimesLessons(lessonplanIndividual);

        unsigned short invalidRoomSameLessonTimes = this->checkRoomWithSameTimesLessons(lessonplanIndividual);

        unsigned short invalidTeacherChangesForClassesSubjects = this->checkTeacherChangesForClassesSubjects(lessonplanIndividual);

        //-1pt - for each lesson deviated from lessons in other days
        unsigned short invalidDifferenceBetweenStartLessons = this->checkStartLessonsDifferenceBetweenDays(lessonplanIndividual);

        //-1pt - for each deviated hour between the days of the week
        unsigned short invalidDifferenceBetweenLessonsCount = this->checkLessonsCountDifferenceBetweenDays(lessonplanIndividual);

        //-1pt - for each free period between lessons
        unsigned short invalidFreePeriodsCountBetweenLessons = this->checkFreePeriodsExistenceBetweenLessons(lessonplanIndividual);

        vector<vector<int>> grades = *new vector<vector<int>>(
                2
        );

        grades[0] = *new vector<int>(
                LessonplanScoreList::hardScoresTypes
        );
        grades[1] = *new vector<int>(
                LessonplanScoreList::softScoresTypes
        );

        grades[0][0] = 0 - invalidClassSubjectSameLessonsTimes;
        grades[0][1] = 0 - invalidTeacherSameLessonsTimes;
        grades[0][2] = 0 - invalidRoomSameLessonTimes;
        grades[0][3] = 0 - invalidTeacherChangesForClassesSubjects;
        grades[1][0] = 0 - invalidDifferenceBetweenStartLessons;
        grades[1][1] = 0 - invalidDifferenceBetweenLessonsCount;
        grades[1][2] = 0 - invalidFreePeriodsCountBetweenLessons;

        return grades;
    }

    unsigned short SchedulingProblem::checkClassesSubjectsWithSameTimesLessons(
            LessonplanIndividual *lessonplanIndividual
    ) {
        LessonplanIndividualDescriptor* lessonplanIndividualDescriptor = lessonplanIndividual->getLessonplanIndividualDescriptor();

        unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();
        unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
        unsigned short classesCount = schedulingProblemProperties->getClassesCount();

        unsigned short classesSubjectsSameTimeSlotsCount = 0;

        // Iterate through list of week days
        for (unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {

            // Iterate through list of lessons
            for (unsigned short lessonIdx = 0; lessonIdx < lessonsCount; lessonIdx++) {

                // Iterate through list of teachers
                for (unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {

                    unsigned short assignedLessonAndDayToClassCount = lessonplanIndividualDescriptor->getAssignedLessonAndDayToClass(weekDayIdx, lessonIdx, classIdx);

                    if (assignedLessonAndDayToClassCount > 1) {
                        classesSubjectsSameTimeSlotsCount += assignedLessonAndDayToClassCount - 1;
                    }
                }
            }
        }

        return classesSubjectsSameTimeSlotsCount;
    }

    unsigned short SchedulingProblem::checkTeachersWithSameTimesLessons(
            LessonplanIndividual *lessonplanIndividual
    ) {
        LessonplanIndividualDescriptor* lessonplanIndividualDescriptor = lessonplanIndividual->getLessonplanIndividualDescriptor();

        unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();
        unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
        unsigned short teachersCount = schedulingProblemProperties->getTeachersCount();

        unsigned short teachersSameTimeSlotsCount = 0;

        // Iterate through list of week days
        for (unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {

            // Iterate through list of lessons
            for (unsigned short lessonIdx = 0; lessonIdx < lessonsCount; lessonIdx++) {

                // Iterate through list of teachers
                for (unsigned short teacherIdx = 0; teacherIdx < teachersCount; teacherIdx++) {

                    unsigned short assignedLessonAndDayToTeacherCount = lessonplanIndividualDescriptor->getAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);

                    if (assignedLessonAndDayToTeacherCount > 1) {
                        teachersSameTimeSlotsCount += assignedLessonAndDayToTeacherCount - 1;
                    }
                }
            }
        }

        return teachersSameTimeSlotsCount;
    }

    unsigned short SchedulingProblem::checkRoomWithSameTimesLessons(
            LessonplanIndividual *lessonplanIndividual
    ) {
        LessonplanIndividualDescriptor* lessonplanIndividualDescriptor = lessonplanIndividual->getLessonplanIndividualDescriptor();

        unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();
        unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
        unsigned short roomsCount = schedulingProblemProperties->getRoomsCount();

        unsigned short roomsSameTimeSlotsCount = 0;

        // Iterate through list of week days
        for (unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {

            // Iterate through list of lessons
            for (unsigned short lessonIdx = 0; lessonIdx < lessonsCount; lessonIdx++) {

                // Iterate through list of rooms
                for (unsigned short roomIdx = 0; roomIdx < roomsCount; roomIdx++) {

                    unsigned short assignedLessonAndDayToRoomCount = lessonplanIndividualDescriptor->getAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

                    if (assignedLessonAndDayToRoomCount > 1) {
                        roomsSameTimeSlotsCount += assignedLessonAndDayToRoomCount - 1;
                    }
                }
            }
        }

        return roomsSameTimeSlotsCount;
    }

    unsigned short SchedulingProblem::checkTeacherChangesForClassesSubjects(
            LessonplanIndividual *lessonplanIndividual
    ) {
        LessonplanIndividualDescriptor* lessonplanIndividualDescriptor = lessonplanIndividual->getLessonplanIndividualDescriptor();

        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
        unsigned short classesCount = this->schedulingProblemProperties->getClassesCount();
        unsigned short subjectsCount = this->schedulingProblemProperties->getSubjectsCount();
        unsigned short teachersCount = this->schedulingProblemProperties->getTeachersCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();

        vector<vector<unsigned short>> assignedTeachersToClassesSubjects = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        subjectsCount, 0
                )
        );
        lessonplanIndividualDescriptor->setAssignedTeachersToClassesSubjectsWrong(assignedTeachersToClassesSubjects);

        vector<vector<unsigned short>> lastAssignedTeachersIdsToClassesSubjects = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        subjectsCount, 0
                )
        );

        for(unsigned int dataIdx = 0; dataIdx < maxDataCount; dataIdx++) {
            unsigned short classIdx = lessonplan[dataIdx][2] - 1;
            unsigned short subjectIdx = lessonplan[dataIdx][3] - 1;

            unsigned short teacherId = lessonplan[dataIdx][4];

            unsigned short lastAssignedTeacherId = lastAssignedTeachersIdsToClassesSubjects[classIdx][subjectIdx];
            if (lastAssignedTeacherId == 0) {
                lastAssignedTeachersIdsToClassesSubjects[classIdx][subjectIdx] = teacherId;
            } else if (lastAssignedTeacherId != teacherId) {
                lessonplanIndividualDescriptor->setAssignedTeachersToClassSubjectWrong(classIdx, subjectIdx, 1);
            }
        }

        unsigned short teachersChangesForClassesSubjectsCount = 0;

        // Iterate through list of week days
        for (unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {

            // Iterate through list of lessons
            for (unsigned short subjectIdx = 0; subjectIdx < subjectsCount; subjectIdx++) {

                unsigned short assignedTeachersToClassSubjectWrong = lessonplanIndividualDescriptor->getAssignedTeachersToClassSubjectWrong(
                        classIdx, subjectIdx);

                if (assignedTeachersToClassSubjectWrong > 0) {
                    teachersChangesForClassesSubjectsCount += 1;
                }
            }
        }

        return teachersChangesForClassesSubjectsCount;
    }

    unsigned short SchedulingProblem::checkStartLessonsDifferenceBetweenDays(
            LessonplanIndividual* lessonplanIndividual
    ) {
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
        unsigned short classesCount = this->schedulingProblemProperties->getClassesCount();
        unsigned short weekDaysCount = this->schedulingProblemProperties->getWeekDaysCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();

        vector<vector<unsigned short>> classesWeekDayStartLessonId = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );

        vector<unsigned short> classesStartLessonsDifferenceCountAverage = *new vector<unsigned short>(
                classesCount, 0
        );

        for(unsigned int dataIdx = 0; dataIdx < maxDataCount; dataIdx++) {
            unsigned short weekDayId = lessonplan[dataIdx][0];
            unsigned short lessonId = lessonplan[dataIdx][1];
            unsigned short classId = lessonplan[dataIdx][2];

            unsigned short classWeekDayStartLessonId = classesWeekDayStartLessonId[classId - 1][weekDayId - 1];

            if (classWeekDayStartLessonId == 0) {
                classesWeekDayStartLessonId[classId - 1][weekDayId - 1] = lessonId;
                continue;
            }

            if (lessonId < classWeekDayStartLessonId) {
                classesWeekDayStartLessonId[classId - 1][weekDayId - 1] = lessonId;
            }
        }

        unsigned short startLessonsDifferencesCount = 0;

        for(unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short classDifferencesCountForAllWeekDays = 0;
            unsigned short weekDaysWithoutLessons = 0;

            for(unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short startLessonIdInAnotherDay = classesWeekDayStartLessonId[classIdx][weekDayIdx];

                if (startLessonIdInAnotherDay == 0) {
                    weekDaysWithoutLessons++;
                } else {
                    for(unsigned short weekDayIdx2 = 0; weekDayIdx2 < weekDaysCount; weekDayIdx2++) {
                        unsigned short startLessonIdInAnotherDay2 = classesWeekDayStartLessonId[classIdx][weekDayIdx2];

                        if (startLessonIdInAnotherDay2 != 0) {
                            classDifferencesCountForAllWeekDays += abs(startLessonIdInAnotherDay - startLessonIdInAnotherDay2);
                        }
                    }
                }
            }

            unsigned short availableWeekDays = weekDaysCount - weekDaysWithoutLessons;
            if (availableWeekDays != 0) {
                auto classDifferencesCountAverage = static_cast<unsigned short>(classDifferencesCountForAllWeekDays / availableWeekDays);
                classesStartLessonsDifferenceCountAverage[classIdx] = classDifferencesCountAverage;
                startLessonsDifferencesCount += classDifferencesCountAverage;
            }
        }

        lessonplanIndividual->getLessonplanIndividualDescriptor()->setClassesStartLessonsDifferenceCountAverage(classesStartLessonsDifferenceCountAverage);

        return startLessonsDifferencesCount;
    }

    unsigned short SchedulingProblem::checkLessonsCountDifferenceBetweenDays(
            LessonplanIndividual* lessonplanIndividual
    ) {
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
        unsigned short classesCount = this->schedulingProblemProperties->getClassesCount();
        unsigned short weekDaysCount = this->schedulingProblemProperties->getWeekDaysCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();

        vector<vector<unsigned short>> classesWeekDayLessonsCount = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );

        vector<unsigned short> classesLessonsCountDifferenceBetweenDaysAverage = *new vector<unsigned short>(
                classesCount, 0
        );

        for(unsigned int dataIdx = 0; dataIdx < maxDataCount; dataIdx++) {
            unsigned short weekDayId = lessonplan[dataIdx][0];
            unsigned short classId = lessonplan[dataIdx][2];

            classesWeekDayLessonsCount[classId - 1][weekDayId - 1]++;
        }

        unsigned short lessonsDifferencesCount = 0;

        for(unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short classDifferencesCountForAllWeekDays = 0;

            for(unsigned short weekDayIdx = 1; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short lessonsCountInAnotherDay = classesWeekDayLessonsCount[classIdx][weekDayIdx];

                for(unsigned short weekDayIdx2 = 0; weekDayIdx2 < weekDaysCount; weekDayIdx2++) {
                    unsigned short lessonsCountInAnotherDay2 = classesWeekDayLessonsCount[classIdx][weekDayIdx2];

                    classDifferencesCountForAllWeekDays += abs(lessonsCountInAnotherDay - lessonsCountInAnotherDay2);
                }
            }

            auto classDifferencesCountAverage = static_cast<unsigned short>(classDifferencesCountForAllWeekDays / weekDaysCount);
            classesLessonsCountDifferenceBetweenDaysAverage[classIdx] = classDifferencesCountAverage;
            lessonsDifferencesCount += classDifferencesCountAverage;
        }

        lessonplanIndividual->getLessonplanIndividualDescriptor()->setClassesLessonsCountAverageDifferenceBetweenDays(classesLessonsCountDifferenceBetweenDaysAverage);

        return lessonsDifferencesCount;
    }

    unsigned short SchedulingProblem::checkFreePeriodsExistenceBetweenLessons(
            LessonplanIndividual *lessonplanIndividual
    ) {
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
        unsigned short classesCount = this->schedulingProblemProperties->getClassesCount();
        unsigned short weekDaysCount = this->schedulingProblemProperties->getWeekDaysCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();

        vector<vector<unsigned short>> classesWeekDayStartLessonId = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );
        vector<vector<unsigned short>> classesWeekDayEndLessonId = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );

        vector<vector<unsigned short>> classesWeekDayFreePeriods = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );

        vector<unsigned short> classesFreePeriodsExistenceBetweenLessonsCount = *new vector<unsigned short>(
                classesCount, 0
        );

        for(unsigned int dataIdx = 0; dataIdx < maxDataCount; dataIdx++) {
            unsigned short weekDayId = lessonplan[dataIdx][0];
            unsigned short lessonId = lessonplan[dataIdx][1];
            unsigned short classId = lessonplan[dataIdx][2];

            unsigned short classWeekDayStartLessonId = classesWeekDayStartLessonId[classId - 1][weekDayId - 1];
            unsigned short classWeekDayEndLessonId = classesWeekDayEndLessonId[classId - 1][weekDayId - 1];

            if (classWeekDayStartLessonId == 0) {
                classesWeekDayStartLessonId[classId - 1][weekDayId - 1] = lessonId;
                classesWeekDayEndLessonId[classId - 1][weekDayId - 1] = lessonId;
                continue;
            }

            if (lessonId < classWeekDayStartLessonId) {
                classesWeekDayStartLessonId[classId - 1][weekDayId - 1] = lessonId;
                unsigned short lessonsDifference = classWeekDayStartLessonId - lessonId;

                if (lessonsDifference > 1) {
                    classesWeekDayFreePeriods[classId - 1][weekDayId - 1] += lessonsDifference - 1;
                }
            } else if (lessonId > classWeekDayEndLessonId) {
                classesWeekDayEndLessonId[classId - 1][weekDayId - 1] = lessonId;
                unsigned short lessonsDifference = lessonId - classWeekDayEndLessonId;

                if (lessonsDifference > 1) {
                    classesWeekDayFreePeriods[classId - 1][weekDayId - 1] += lessonsDifference - 1;
                }
            } else {
                if (classesWeekDayFreePeriods[classId - 1][weekDayId - 1] > 0) {
                    classesWeekDayFreePeriods[classId - 1][weekDayId - 1]--;
                }
            }

        }

        unsigned short classesFreePeriodsCount = 0;

        for(unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            for(unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short freePeriodsCountInAnotherDay = classesWeekDayFreePeriods[classIdx][weekDayIdx];

                classesFreePeriodsCount += freePeriodsCountInAnotherDay;
                classesFreePeriodsExistenceBetweenLessonsCount[classIdx] += freePeriodsCountInAnotherDay;
            }
        }

        lessonplanIndividual->getLessonplanIndividualDescriptor()->setClassesFreePeriodsExistenceBetweenLessonsCount(classesFreePeriodsExistenceBetweenLessonsCount);

        return classesFreePeriodsCount;
    }

    SchedulingProblemProperties *SchedulingProblem::getSchedulingProblemProperties() const {
        return schedulingProblemProperties;
    }

}