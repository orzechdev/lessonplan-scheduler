#include <numeric>
#include <chrono>
#include <random>
#include <algorithm>
#include "LessonplanIndividualAbstractFactory.hpp"
#include "RandomNumberGenerator.hpp"

namespace lessonplans {

    LessonplanIndividual *LessonplanIndividualAbstractFactory::createLessonplanIndividual(
            SchedulingProblemProperties *schedulingProblemProperties
    ) {
        auto *lessonplanIndividual = new LessonplanIndividual();

        unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();
        unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
        unsigned short classesCount = schedulingProblemProperties->getClassesCount();
        unsigned short teachersCount = schedulingProblemProperties->getTeachersCount();
        unsigned short roomsCount = schedulingProblemProperties->getRoomsCount();

        unsigned int maxDataCount = LessonplanIndividualAbstractFactory::calculateMaxDataCount(
                schedulingProblemProperties);

        vector<vector<unsigned short>> lessonplan = *new vector<vector<unsigned short>>(
                maxDataCount, vector<unsigned short>(
                        LessonplanIndividual::dataTypes
                )
        );

        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses = *new vector<vector<vector<unsigned short>>>(
                weekDaysCount, vector<vector<unsigned short>>(
                        lessonsCount, vector<unsigned short>(
                                classesCount, 0
                        )
                )
        );
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers = *new vector<vector<vector<unsigned short>>>(
                weekDaysCount, vector<vector<unsigned short>>(
                        lessonsCount, vector<unsigned short>(
                                teachersCount, 0
                        )
                )
        );
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms = *new vector<vector<vector<unsigned short>>>(
                weekDaysCount, vector<vector<unsigned short>>(
                        lessonsCount, vector<unsigned short>(
                                roomsCount, 0
                        )
                )
        );

        lessonplanIndividual->setMaxDataCount(maxDataCount);
        lessonplanIndividual->setLessonplan(lessonplan);
        lessonplanIndividual->setAssignedLessonAndDaysToClasses(assignedLessonAndDaysToClasses);
        lessonplanIndividual->setAssignedLessonAndDaysToTeachers(assignedLessonAndDaysToTeachers);
        lessonplanIndividual->setAssignedLessonAndDaysToRooms(assignedLessonAndDaysToRooms);

        LessonplanIndividualAbstractFactory::assignClassesWithSubjects(lessonplanIndividual,
                                                                       schedulingProblemProperties);

        return lessonplanIndividual;
    }

    void LessonplanIndividualAbstractFactory::assignClassesWithSubjects(
            LessonplanIndividual *lessonplanIndividual,
            SchedulingProblemProperties *schedulingProblemProperties
    ) {
        unsigned short individualDataIdx = 0;

        unsigned short classesCount = schedulingProblemProperties->getClassesCount();

        vector<unsigned short> classesIdsSequence = RandomNumberGenerator::getRandomIdsSequence(
                classesCount);

        // Iterate through list of classes
        for (unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short classId = classesIdsSequence[classIdx];
            vector<unsigned short> classSubjects = schedulingProblemProperties->getClassSubjects(classId - 1);
            vector<unsigned short> classSubjectsEachCount = schedulingProblemProperties->getClassSubjectsCount(
                    classId - 1);
            auto classSubjectsCount = static_cast<unsigned short>(classSubjects.size());

            // CLASS OK

            vector<unsigned short> classesSubjectsIdxsSequence = RandomNumberGenerator::getRandomIdxsSequence(
                    classSubjectsCount);

            // Iterate through list of classes subjects
            for (unsigned short subjectIdx = 0; subjectIdx < classSubjectsCount; subjectIdx++) {
                unsigned short classSubjectIdx = classesSubjectsIdxsSequence[subjectIdx];
                unsigned short subjectId = classSubjects[classSubjectIdx];
                unsigned short classSubjectEachCount = classSubjectsEachCount[classSubjectIdx];

                // SUBJECT OK

                for (unsigned short subjectNumber = 1; subjectNumber <= classSubjectEachCount; subjectNumber++) {
                    bool teacherFound = LessonplanIndividualAbstractFactory::tryAssignTeacher(lessonplanIndividual,
                                                                                              schedulingProblemProperties,
                                                                                              individualDataIdx,
                                                                                              classId, subjectId);

                    if (teacherFound) {
                        individualDataIdx++;
                    }
                }
            }
        }
    }

    bool LessonplanIndividualAbstractFactory::tryAssignTeacher(
            LessonplanIndividual *lessonplanIndividual,
            SchedulingProblemProperties *schedulingProblemProperties,
            unsigned short individualDataIdx,
            unsigned short classId, unsigned short subjectId
    ) {
        unsigned short teachersCount = schedulingProblemProperties->getTeachersCount();

        vector<unsigned short> teachersIdsSequence = RandomNumberGenerator::getRandomIdsSequence(
                schedulingProblemProperties->getTeachersCount());

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
                    // TEACHER OK

                    bool roomFound = LessonplanIndividualAbstractFactory::tryAssignRoom(lessonplanIndividual,
                                                                                        schedulingProblemProperties,
                                                                                        individualDataIdx, classId,
                                                                                        subjectId,
                                                                                        teacherId);

                    if (roomFound) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool LessonplanIndividualAbstractFactory::tryAssignRoom(
            LessonplanIndividual *lessonplanIndividual,
            SchedulingProblemProperties *schedulingProblemProperties,
            unsigned short individualDataIdx,
            unsigned short classId, unsigned short subjectId, unsigned short teacherId
    ) {
        unsigned short roomsCount = schedulingProblemProperties->getRoomsCount();

        vector<unsigned short> roomsIdsSequence = RandomNumberGenerator::getRandomIdsSequence(
                schedulingProblemProperties->getRoomsCount());

        // Iterate through list of rooms
        for (unsigned short roomIdx = 0; roomIdx < roomsCount; roomIdx++) {
            unsigned short roomId = roomsIdsSequence[roomIdx];
            vector<unsigned short> roomSubjects = schedulingProblemProperties->getRoomSubjects(roomId - 1);
            auto roomSubjectsCount = static_cast<unsigned short>(roomSubjects.size());

            if (roomSubjectsCount > 0) {
                // Iterate through list of rooms subjects
                for (unsigned short subjectIdx3 = 0; subjectIdx3 < roomSubjectsCount; subjectIdx3++) {
                    unsigned short subjectId3 = roomSubjects[subjectIdx3];

                    if (subjectId == subjectId3) {
                        // ROOM OK

                        bool weekDayAndLessonFound = LessonplanIndividualAbstractFactory::tryAssignWeekDayAndLesson(
                                lessonplanIndividual,
                                schedulingProblemProperties,
                                individualDataIdx, classId,
                                subjectId, teacherId, roomId);

                        if (weekDayAndLessonFound) {
                            return true;
                        }
                    }
                }
            } else {
                // ROOM OK

                bool weekDayAndLessonFound = LessonplanIndividualAbstractFactory::tryAssignWeekDayAndLesson(
                        lessonplanIndividual,
                        schedulingProblemProperties,
                        individualDataIdx, classId, subjectId, teacherId,
                        roomId);

                if (weekDayAndLessonFound) {
                    return true;
                }
            }
        }

        return false;
    }

    bool LessonplanIndividualAbstractFactory::tryAssignWeekDayAndLesson(
            LessonplanIndividual *lessonplanIndividual,
            SchedulingProblemProperties *schedulingProblemProperties,
            unsigned short individualDataIdx,
            unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId
    ) {
        unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();
        unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();

        vector<unsigned short> lessonsIdsSequence = RandomNumberGenerator::getRandomIdsSequence(
                schedulingProblemProperties->getLessonsCount());

        // Iterate through list of lessons
        for (unsigned short lessonIdx = 0; lessonIdx < lessonsCount; lessonIdx++) {
            unsigned short lessonId = lessonsIdsSequence[lessonIdx];

            vector<unsigned short> weekDaysIdsSequence = RandomNumberGenerator::getRandomIdsSequence(
                    schedulingProblemProperties->getWeekDaysCount());

            // Iterate through list of week days
            for (unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short weekDayId = weekDaysIdsSequence[weekDayIdx];
                unsigned short currentWeekDayIdx = weekDayId - 1;
                unsigned short currentLessonIdx = lessonId - 1;

                if (
                        !lessonplanIndividual->getAssignedLessonAndDayToClass(currentWeekDayIdx, currentLessonIdx,
                                                                              classId - 1)
                        && !lessonplanIndividual->getAssignedLessonAndDayToTeacher(currentWeekDayIdx, currentLessonIdx,
                                                                                   teacherId - 1)
                        && !lessonplanIndividual->getAssignedLessonAndDayToRoom(currentWeekDayIdx, currentLessonIdx,
                                                                                roomId - 1)
                        ) {
                    // WEEK DAY AND LESSON OK

                    lessonplanIndividual->increaseAssignedLessonAndDayToClass(currentWeekDayIdx, currentLessonIdx,
                                                                         classId - 1);
                    lessonplanIndividual->increaseAssignedLessonAndDayToTeacher(currentWeekDayIdx, currentLessonIdx,
                                                                           teacherId - 1);
                    lessonplanIndividual->increaseAssignedLessonAndDayToRoom(currentWeekDayIdx, currentLessonIdx,
                                                                        roomId - 1);

                    lessonplanIndividual->setLessonplanDataItem(individualDataIdx, weekDayId, lessonId, classId,
                                                                subjectId, teacherId, roomId);

                    return true;
                }
            }
        }

        return false;
    }

    unsigned int LessonplanIndividualAbstractFactory::calculateMaxDataCount(
            SchedulingProblemProperties *schedulingProblemProperties) {
        unsigned int maxDataCount = 0;

        unsigned short classesCount = schedulingProblemProperties->getClassesCount();

        for (unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            auto classSubjectsEachCount = schedulingProblemProperties->getClassSubjectsCount(classIdx);

            std::for_each(classSubjectsEachCount.begin(), classSubjectsEachCount.end(), [&] (unsigned short classSubjectNCount) {
                maxDataCount += classSubjectNCount;
            });
        }

        return maxDataCount;
    }
}
