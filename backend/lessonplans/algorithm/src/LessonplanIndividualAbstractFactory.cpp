#include <numeric>
#include <chrono>
#include <random>
#include <algorithm>
#include "LessonplanIndividualAbstractFactory.hpp"

namespace lessonplans {

    LessonplanIndividual *LessonplanIndividualAbstractFactory::createLessonplanIndividual(
            LessonplanSchedulingProblemProperties *lessonplanSchedulingProblemProperties
    ) {
        auto *lessonplanIndividual = new LessonplanIndividual();

        unsigned short weekDaysCount = lessonplanSchedulingProblemProperties->getWeekDaysCount();
        unsigned short lessonsCount = lessonplanSchedulingProblemProperties->getLessonsCount();
        unsigned short classesCount = lessonplanSchedulingProblemProperties->getClassesCount();
        unsigned short teachersCount = lessonplanSchedulingProblemProperties->getTeachersCount();
        unsigned short roomsCount = lessonplanSchedulingProblemProperties->getRoomsCount();

        unsigned int maxDataCount = LessonplanIndividualAbstractFactory::calculateMaxDataCount(
                lessonplanSchedulingProblemProperties);

        vector<vector<unsigned short>> lessonplan = *new vector<vector<unsigned short>>(
                maxDataCount, vector<unsigned short>(
                        LessonplanIndividual::dataTypes
                )
        );

        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses = *new vector<vector<vector<unsigned short>>>(
                weekDaysCount, vector<vector<unsigned short>>(
                        lessonsCount, vector<unsigned short>(
                                classesCount
                        )
                )
        );
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers = *new vector<vector<vector<unsigned short>>>(
                weekDaysCount, vector<vector<unsigned short>>(
                        lessonsCount, vector<unsigned short>(
                                teachersCount
                        )
                )
        );
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms = *new vector<vector<vector<unsigned short>>>(
                weekDaysCount, vector<vector<unsigned short>>(
                        lessonsCount, vector<unsigned short>(
                                roomsCount
                        )
                )
        );

        lessonplanIndividual->setMaxDataCount(maxDataCount);
        lessonplanIndividual->setLessonplan(lessonplan);
        lessonplanIndividual->setAssignedLessonAndDaysToClasses(assignedLessonAndDaysToClasses);
        lessonplanIndividual->setAssignedLessonAndDaysToTeachers(assignedLessonAndDaysToTeachers);
        lessonplanIndividual->setAssignedLessonAndDaysToRooms(assignedLessonAndDaysToRooms);

        LessonplanIndividualAbstractFactory::assignClassesWithSubjects(lessonplanIndividual,
                                                                       lessonplanSchedulingProblemProperties);

        return lessonplanIndividual;
    }

    void LessonplanIndividualAbstractFactory::assignClassesWithSubjects(
            LessonplanIndividual *lessonplanIndividual,
            LessonplanSchedulingProblemProperties *lessonplanSchedulingProblemProperties
    ) {
        unsigned short individualDataIdx = 0;

        unsigned short classesCount = lessonplanSchedulingProblemProperties->getClassesCount();

        vector<unsigned short> classesIdsSequence = LessonplanIndividualAbstractFactory::getRandomIdsSequence(
                classesCount);

        // Iterate through list of classes
        for (unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short classId = classesIdsSequence[classIdx];
            vector<unsigned short> classSubjects = lessonplanSchedulingProblemProperties->getClassSubjects(classId - 1);
            vector<unsigned short> classSubjectsEachCount = lessonplanSchedulingProblemProperties->getClassSubjectsCount(
                    classId - 1);
            auto classSubjectsCount = static_cast<unsigned short>(classSubjects.size());

            // CLASS OK

            vector<unsigned short> classesSubjectsIdxsSequence = LessonplanIndividualAbstractFactory::getRandomIdxsSequence(
                    classSubjectsCount);

            // Iterate through list of classes subjects
            for (unsigned short subjectIdx = 0; subjectIdx < classSubjectsCount; subjectIdx++) {
                unsigned short classSubjectIdx = classesSubjectsIdxsSequence[subjectIdx];
                unsigned short subjectId = classSubjects[classSubjectIdx];
                unsigned short classSubjectEachCount = classSubjectsEachCount[classSubjectIdx];

                // SUBJECT OK

                for (unsigned short subjectNumber = 1; subjectNumber <= classSubjectEachCount; subjectNumber++) {
                    bool teacherFound = LessonplanIndividualAbstractFactory::tryAssignTeacher(lessonplanIndividual,
                                                                                              lessonplanSchedulingProblemProperties,
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
            LessonplanSchedulingProblemProperties *lessonplanSchedulingProblemProperties,
            unsigned short individualDataIdx,
            unsigned short classId, unsigned short subjectId
    ) {
        unsigned short teachersCount = lessonplanSchedulingProblemProperties->getTeachersCount();

        vector<unsigned short> teachersIdsSequence = LessonplanIndividualAbstractFactory::getRandomIdsSequence(
                lessonplanSchedulingProblemProperties->getTeachersCount());

        // Iterate through list of teachers
        for (unsigned short teacherIdx = 0; teacherIdx < teachersCount; teacherIdx++) {
            unsigned short teacherId = teachersIdsSequence[teacherIdx];
            vector<unsigned short> teacherSubjects = lessonplanSchedulingProblemProperties->getTeacherSubjects(
                    teacherId - 1);
            auto teacherSubjectsCount = static_cast<unsigned short>(teacherSubjects.size());

            // Iterate through list of teachers subjects
            for (unsigned short subjectIdx2 = 0; subjectIdx2 < teacherSubjectsCount; subjectIdx2++) {
                unsigned short subjectId2 = teacherSubjects[subjectIdx2];

                if (subjectId == subjectId2) {
                    // TEACHER OK

                    bool roomFound = LessonplanIndividualAbstractFactory::tryAssignRoom(lessonplanIndividual,
                                                                                        lessonplanSchedulingProblemProperties,
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
            LessonplanSchedulingProblemProperties *lessonplanSchedulingProblemProperties,
            unsigned short individualDataIdx,
            unsigned short classId, unsigned short subjectId, unsigned short teacherId
    ) {
        unsigned short roomsCount = lessonplanSchedulingProblemProperties->getRoomsCount();

        vector<unsigned short> roomsIdsSequence = LessonplanIndividualAbstractFactory::getRandomIdsSequence(
                lessonplanSchedulingProblemProperties->getRoomsCount());

        // Iterate through list of rooms
        for (unsigned short roomIdx = 0; roomIdx < roomsCount; roomIdx++) {
            unsigned short roomId = roomsIdsSequence[roomIdx];
            vector<unsigned short> roomSubjects = lessonplanSchedulingProblemProperties->getRoomSubjects(roomId - 1);
            auto roomSubjectsCount = static_cast<unsigned short>(roomSubjects.size());

            if (roomSubjectsCount > 0) {
                // Iterate through list of rooms subjects
                for (unsigned short subjectIdx3 = 0; subjectIdx3 < roomSubjectsCount; subjectIdx3++) {
                    unsigned short subjectId3 = roomSubjects[subjectIdx3];

                    if (subjectId == subjectId3) {
                        // ROOM OK

                        bool weekDayAndLessonFound = LessonplanIndividualAbstractFactory::tryAssignWeekDayAndLesson(
                                lessonplanIndividual,
                                lessonplanSchedulingProblemProperties,
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
                        lessonplanSchedulingProblemProperties,
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
            LessonplanSchedulingProblemProperties *lessonplanSchedulingProblemProperties,
            unsigned short individualDataIdx,
            unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId
    ) {
        unsigned short weekDaysCount = lessonplanSchedulingProblemProperties->getWeekDaysCount();
        unsigned short lessonsCount = lessonplanSchedulingProblemProperties->getLessonsCount();

        vector<unsigned short> lessonsIdsSequence = LessonplanIndividualAbstractFactory::getRandomIdsSequence(
                lessonplanSchedulingProblemProperties->getLessonsCount());

        // Iterate through list of lessons
        for (unsigned short lessonIdx = 0; lessonIdx < lessonsCount; lessonIdx++) {
            unsigned short lessonId = lessonsIdsSequence[lessonIdx];

            vector<unsigned short> weekDaysIdsSequence = LessonplanIndividualAbstractFactory::getRandomIdsSequence(
                    lessonplanSchedulingProblemProperties->getWeekDaysCount());

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

                    lessonplanIndividual->setAssignedLessonAndDayToClass(currentWeekDayIdx, currentLessonIdx,
                                                                         classId - 1);
                    lessonplanIndividual->setAssignedLessonAndDayToTeacher(currentWeekDayIdx, currentLessonIdx,
                                                                           teacherId - 1);
                    lessonplanIndividual->setAssignedLessonAndDayToRoom(currentWeekDayIdx, currentLessonIdx,
                                                                        roomId - 1);

                    lessonplanIndividual->setLessonplanDataItem(individualDataIdx, weekDayId, lessonId, classId,
                                                                subjectId, teacherId, roomId);

                    return true;
                }
            }
        }

        return false;
    }

    vector<unsigned short> LessonplanIndividualAbstractFactory::getRandomIdxsSequence(unsigned short sequenceSize) {
        return LessonplanIndividualAbstractFactory::getRandomNumbersSequence(sequenceSize, 0);
    }

    vector<unsigned short> LessonplanIndividualAbstractFactory::getRandomIdsSequence(unsigned short sequenceSize) {
        return LessonplanIndividualAbstractFactory::getRandomNumbersSequence(sequenceSize, 1);
    }

    vector<unsigned short> LessonplanIndividualAbstractFactory::getRandomNumbersSequence(unsigned short sequenceSize,
                                                                                         unsigned short lowestNumber) {
        // Init vector with required size
        vector<unsigned short> sequence = *new vector<unsigned short>(
                sequenceSize
        );

        // Populate vector with increasing numbers
        std::iota(std::begin(sequence), std::end(sequence), lowestNumber);

        // Init random engine with unusual seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine randomEngine(seed);

        // Shuffle numbers in vector with random engine to obtain theirs random distribution
        std::shuffle(std::begin(sequence), std::end(sequence), randomEngine);

        return sequence;
    }

    unsigned int LessonplanIndividualAbstractFactory::calculateMaxDataCount(
            LessonplanSchedulingProblemProperties *lessonplanSchedulingProblemProperties) {
        unsigned int maxDataCount = 0;

        unsigned short classesCount = lessonplanSchedulingProblemProperties->getClassesCount();

        for (unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            auto classSubjectsEachCount = lessonplanSchedulingProblemProperties->getClassSubjectsCount(classIdx);

            std::for_each(classSubjectsEachCount.begin(), classSubjectsEachCount.end(), [&] (unsigned short classSubjectNCount) {
                maxDataCount += classSubjectNCount;
            });
        }

        return maxDataCount;
    }
}
