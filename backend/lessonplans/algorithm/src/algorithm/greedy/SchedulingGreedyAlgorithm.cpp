#include <algorithm>
#include "../../../include/algorithm/greedy/SchedulingGreedyAlgorithm.hpp"
#include "../../../include/utils/RandomNumberGenerator.hpp"

namespace lessonplans {

    SchedulingGreedyAlgorithm::SchedulingGreedyAlgorithm(int iterationsCount) {
        this->iterationsCount = iterationsCount;

        this->individualsHardScores = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::hardScoresTypes
                )
        );
        this->individualsSoftScores = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::softScoresTypes
                )
        );
        this->individualsSummaryHardScores = *new vector<int>(
                this->iterationsCount
        );
        this->individualsSummarySoftScores = *new vector<int>(
                this->iterationsCount
        );
    }

    SchedulingSolution *SchedulingGreedyAlgorithm::findBestLessonplan(SchedulingProblem *schedulingProblem) {
        this->bestIndividual = schedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(this->bestIndividual);

        this->individualsHardScores[0] = obtainedScores[0];
        this->individualsSoftScores[0] = obtainedScores[1];

        this->individualsSummaryHardScores[0] = SchedulingProblem::calculateSummaryScore(obtainedScores[0]);
        this->individualsSummarySoftScores[0] = SchedulingProblem::calculateSummaryScore(obtainedScores[1]);

        int bestIndividualIdx = 0;

        for (int i = 1; i < this->iterationsCount; i++) {
            LessonplanIndividual *currentIndividual = this->reformLessonplan(this->bestIndividual, schedulingProblem);
            obtainedScores = schedulingProblem->evaluateLessonplan(currentIndividual);

            this->individualsHardScores[i] = obtainedScores[0];
            this->individualsSoftScores[i] = obtainedScores[1];

            this->individualsSummaryHardScores[i] = SchedulingProblem::calculateSummaryScore(obtainedScores[0]);
            this->individualsSummarySoftScores[i] = SchedulingProblem::calculateSummaryScore(obtainedScores[1]);

            bestIndividualIdx = i;
            this->bestIndividual = currentIndividual;
        }

        auto *lessonplanSchedulingSoultion = new SchedulingSolution(
                this->bestIndividual,
                this->individualsHardScores,
                this->individualsSoftScores,
                this->individualsSummaryHardScores,
                this->individualsSummarySoftScores,
                bestIndividualIdx
        );

        return lessonplanSchedulingSoultion;
    }

    LessonplanIndividual *SchedulingGreedyAlgorithm::reformLessonplan(LessonplanIndividual *lessonplanIndividual,
                                                                      SchedulingProblem *schedulingProblem) {
        /*
         * Class is const
         * Subject is const
         *
         * Weekday may change
         * Lesson may change
         * Teacher may change (but for each class and subject pair it must be always the same)
         * Room may change
         */

        SchedulingProblemProperties *schedulingProblemProperties = schedulingProblem->getSchedulingProblemProperties();
        LessonplanIndividualDescriptor *lessonplanIndividualDescriptor = lessonplanIndividual->getLessonplanIndividualDescriptor();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();

        vector<unsigned short> dataItemIdxsSequence = RandomNumberGenerator::getRandomIdxsSequence(maxDataCount);

        unsigned short classesCount = schedulingProblemProperties->getClassesCount();
        unsigned short subjectsCount = schedulingProblemProperties->getSubjectsCount();

        vector<vector<unsigned short>> classesSubjectsTeachersToAssign = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        subjectsCount, 0
                )
        );

        for (unsigned int dataIdxNum = 0; dataIdxNum < maxDataCount; dataIdxNum++) {
            unsigned short dataIdx = dataItemIdxsSequence[dataIdxNum];

            vector<unsigned short> *lessonplanDataItem = &lessonplan[dataIdx];

            this->reformLessonplanTeacherDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                                  lessonplanDataItem);
            this->reformLessonplanRoomDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                               lessonplanDataItem);
            this->reformLessonplanClassSubjectTeacher(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                                      lessonplanDataItem,
                                                      &classesSubjectsTeachersToAssign);
            this->reformLessonplanClassSubjectDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                                       lessonplanDataItem);

            lessonplanIndividual->setLessonplan(lessonplan);
//            schedulingProblem->evaluateLessonplan(lessonplanIndividual);
        }

        lessonplanIndividual->setLessonplan(lessonplan);

        return lessonplanIndividual;
    }


    void SchedulingGreedyAlgorithm::reformLessonplanTeacherDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem) {

        unsigned short teachersCount = schedulingProblemProperties->getTeachersCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short teacherIdx = (*lessonplanDataItem)[4] - 1;

        unsigned short prevAssignedLessonAndDayToTeacher = lessonplanIndividualDescriptor->getAssignedLessonAndDayToTeacher(
                weekDayIdx, lessonIdx, teacherIdx);

        if (prevAssignedLessonAndDayToTeacher > 1) {
            unsigned short teacherIdToChange = RandomNumberGenerator::getRandomNumber(1, teachersCount);

            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);

            (*lessonplanDataItem)[4] = teacherIdToChange;
            unsigned short teacherIdxToChange = teacherIdToChange - 1;

            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx,
                                                                                  teacherIdxToChange);
        }
    }

    void SchedulingGreedyAlgorithm::reformLessonplanRoomDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem) {
        unsigned short roomsCount = schedulingProblemProperties->getRoomsCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short roomIdx = (*lessonplanDataItem)[5] - 1;

        unsigned short prevAssignedLessonAndDayToRoom = lessonplanIndividualDescriptor->getAssignedLessonAndDayToRoom(
                weekDayIdx, lessonIdx, roomIdx);

        if (prevAssignedLessonAndDayToRoom > 1) {
            unsigned short roomIdToChange = RandomNumberGenerator::getRandomNumber(1, roomsCount);

            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

            (*lessonplanDataItem)[5] = roomIdToChange;
            unsigned short roomIdxToChange = roomIdToChange - 1;

            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdxToChange);
        }
    }

    void SchedulingGreedyAlgorithm::reformLessonplanClassSubjectDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem) {
        unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
        unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short classIdx = (*lessonplanDataItem)[2] - 1;

        unsigned short prevAssignedLessonAndDayToClass = lessonplanIndividualDescriptor->getAssignedLessonAndDayToClass(
                weekDayIdx, lessonIdx, classIdx);
        unsigned short classStartLessonsDifferenceCountAverage = lessonplanIndividualDescriptor->getClassesStartLessonsDifferenceCountAverage()[classIdx];
        unsigned short classLessonsCountDifferenceBetweenDaysAverage = lessonplanIndividualDescriptor->getClassesLessonsCountAverageDifferenceBetweenDays()[classIdx];
        unsigned short classFreePeriodsExistenceBetweenLessonsCount = lessonplanIndividualDescriptor->getClassesFreePeriodsExistenceBetweenLessonsCount()[classIdx];

        if (prevAssignedLessonAndDayToClass > 1 ||
            classStartLessonsDifferenceCountAverage > 1 ||
            classLessonsCountDifferenceBetweenDaysAverage > 1 ||
            classFreePeriodsExistenceBetweenLessonsCount > 0) {
            for (unsigned short lessonIdxToChange = 0; lessonIdxToChange < lessonsCount; lessonIdxToChange++) {
                vector<unsigned short> weekDaysIdxsSequence = RandomNumberGenerator::getRandomIdxsSequence(
                        weekDaysCount);
                for (unsigned short weekDayIdxNum = 0; weekDayIdxNum < weekDaysCount; weekDayIdxNum++) {
                    unsigned short weekDayIdxToChange = weekDaysIdxsSequence[weekDayIdxNum];
                    unsigned short anotherAssignedLessonAndDayToClass = lessonplanIndividualDescriptor->getAssignedLessonAndDayToClass(
                            weekDayIdxToChange, lessonIdxToChange, classIdx);

                    if (anotherAssignedLessonAndDayToClass <= 0) {

                        lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToClass(weekDayIdx, lessonIdx,
                                                                                            classIdx);

                        (*lessonplanDataItem)[0] = weekDayIdxToChange + 1;
                        (*lessonplanDataItem)[1] = lessonIdxToChange + 1;

                        lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(weekDayIdxToChange,
                                                                                            lessonIdxToChange,
                                                                                            classIdx);
                        return;
                    }
                }
            }
        }
    }

    void SchedulingGreedyAlgorithm::reformLessonplanClassSubjectTeacher(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties, vector<unsigned short> *lessonplanDataItem,
            vector<vector<unsigned short>> *classesSubjectsTeachersToAssign) {
        unsigned short classIdx = (*lessonplanDataItem)[2] - 1;
        unsigned short subjectIdx = (*lessonplanDataItem)[3] - 1;

        unsigned short assignedTeachersToClassSubjectWrong = lessonplanIndividualDescriptor->getAssignedTeachersToClassSubjectWrong(
                classIdx, subjectIdx);

        if (assignedTeachersToClassSubjectWrong > 0) {
            unsigned short teacherIdToAssign = (*classesSubjectsTeachersToAssign)[classIdx][subjectIdx];

            if (teacherIdToAssign == 0) {
                (*classesSubjectsTeachersToAssign)[classIdx][subjectIdx] = teacherIdToAssign = SchedulingGreedyAlgorithm::findTeacherForClassSubject(
                        schedulingProblemProperties, subjectIdx + 1);
            }

            (*lessonplanDataItem)[4] = teacherIdToAssign;
        }

    }

    unsigned short
    SchedulingGreedyAlgorithm::findTeacherForClassSubject(SchedulingProblemProperties *schedulingProblemProperties,
                                                          unsigned short subjectId) {
        unsigned short teachersCount = schedulingProblemProperties->getTeachersCount();

        vector<unsigned short> teachersIdsSequence = RandomNumberGenerator::getRandomIdsSequence(teachersCount);

        // Iterate through list of teachers
        for (unsigned short teacherIdx = 0; teacherIdx < teachersCount; teacherIdx++) {
            unsigned short teacherId = teachersIdsSequence[teacherIdx];
            vector<unsigned short> teacherSubjects = schedulingProblemProperties->getTeacherSubjects(
                    teacherId - 1);
            auto teacherSubjectsCount = static_cast<unsigned short>(teacherSubjects.size());

            // Iterate through list of teachers subjects
            for (unsigned short subjectIdx2 = 0; subjectIdx2 < teacherSubjectsCount; subjectIdx2++) {
                unsigned short subjectId2 = teacherSubjects[subjectIdx2];

                if (subjectId == subjectId2) {
                    return teacherId;
                }
            }
        }
    }

}
