#include "LessonplanIndividual.hpp"

#include <utility>
#include <random>
#include <algorithm>
#include <chrono>


namespace lessonplans {

    LessonplanIndividual::LessonplanIndividual(LessonplanData* lessonplanData) {
        unsigned short weekDaysCount = lessonplanData->getWeekDaysCount();
        unsigned short lessonsCount = lessonplanData->getLessonsCount();
        unsigned short classesCount = lessonplanData->getClassesCount();
        unsigned short subjectsCount = lessonplanData->getSubjectsCount();
        unsigned short teachersCount = lessonplanData->getTeachersCount();
        unsigned short roomsCount = lessonplanData->getRoomsCount();

        this->maxDataCount = LessonplanIndividual::calculateMaxDataCount(lessonplanData);

        this->lessonplan = *new vector<vector<unsigned short>>(
                this->maxDataCount, vector<unsigned short>(
                        LessonplanIndividual::dataTypes
                )
        );

        this->assignedLessonAndDaysToClasses = *new vector<vector<vector<unsigned short>>>(
                weekDaysCount, vector<vector<unsigned short>>(
                        lessonsCount, vector<unsigned short>(
                                classesCount
                        )
                )
        );
        this->assignedLessonAndDaysToTeachers = *new vector<vector<vector<unsigned short>>>(
                weekDaysCount, vector<vector<unsigned short>>(
                        lessonsCount, vector<unsigned short>(
                                teachersCount
                        )
                )
        );
        this->assignedLessonAndDaysToRooms = *new vector<vector<vector<unsigned short>>>(
                weekDaysCount, vector<vector<unsigned short>>(
                        lessonsCount, vector<unsigned short>(
                                roomsCount
                        )
                )
        );

        unsigned short individualDataIdx = 0;

        vector<unsigned short> classesIdsSequence = LessonplanIndividual::getRandomIdsSequence(classesCount);

        // Iterate through list of classes
        for (unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short classId = classesIdsSequence[classIdx];
            vector<unsigned short> classSubjects = lessonplanData->getClassSubjects(classId - 1);
            auto classSubjectsCount = static_cast<unsigned short>(classSubjects.size());

            // CLASS OK

            vector<unsigned short> classesSubjectsIdxsSequence = LessonplanIndividual::getRandomIdxsSequence(classSubjectsCount);

            // Iterate through list of classes subjects
            for (unsigned short subjectIdx = 0; subjectIdx < classSubjectsCount; subjectIdx++) {
                unsigned short classSubjectIdx = classesSubjectsIdxsSequence[subjectIdx];
                unsigned short subjectId = classSubjects[classSubjectIdx];

                // SUBJECT OK

                bool teacherFound = this->tryAssignTeacher(lessonplanData, individualDataIdx, classIdx, classId, subjectId);

                if (teacherFound) {
                    individualDataIdx++;
                }
            }
        }
    }

    bool LessonplanIndividual::tryAssignTeacher(
            LessonplanData *lessonplanData,
            unsigned short individualDataIdx,
            unsigned short classIdx,
            unsigned short classId, unsigned short subjectId
    ) {
        unsigned short subjectsCount = lessonplanData->getSubjectsCount();
        unsigned short teachersCount = lessonplanData->getTeachersCount();

        vector<unsigned short> teachersIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getTeachersCount());

        // Iterate through list of teachers
        for (unsigned short teacherIdx = 0; teacherIdx < teachersCount; teacherIdx++) {
            unsigned short teacherId = teachersIdsSequence[teacherIdx];
            vector<unsigned short> teacherSubjects = lessonplanData->getTeacherSubjects(teacherId - 1);
            auto teacherSubjectsCount = static_cast<unsigned short>(teacherSubjects.size());

            // Iterate through list of teachers subjects
            for (unsigned short subjectIdx2 = 0; subjectIdx2 < teacherSubjectsCount; subjectIdx2++) {
                unsigned short subjectId2 = teacherSubjects[subjectIdx2];

                if (subjectId == subjectId2) {
                    // TEACHER OK

                    bool roomFound = this->tryAssignRoom(lessonplanData, individualDataIdx, classIdx, teacherIdx, classId, subjectId, teacherId);

                    if (roomFound) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool LessonplanIndividual::tryAssignRoom(
            LessonplanData *lessonplanData,
            unsigned short individualDataIdx,
            unsigned short classIdx, unsigned short teacherIdx,
            unsigned short classId, unsigned short subjectId, unsigned short teacherId
    ) {
        unsigned short subjectsCount = lessonplanData->getSubjectsCount();
        unsigned short roomsCount = lessonplanData->getRoomsCount();

        vector<unsigned short> roomsIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getRoomsCount());

        // Iterate through list of rooms
        for (unsigned short roomIdx = 0; roomIdx < roomsCount; roomIdx++) {
            unsigned short roomId = roomsIdsSequence[roomIdx];
            vector<unsigned short> roomSubjects = lessonplanData->getRoomSubjects(roomId - 1);
            auto roomSubjectsCount = static_cast<unsigned short>(roomSubjects.size());

            if (roomSubjectsCount > 0) {
                // Iterate through list of rooms subjects
                for (unsigned short subjectIdx3 = 0; subjectIdx3 < roomSubjectsCount; subjectIdx3++) {
                    unsigned short subjectId3 = roomSubjects[subjectIdx3];

                    if (subjectId == subjectId3) {
                        // ROOM OK

                        bool weekDayAndLessonFound = this->tryAssignWeekDayAndLesson(lessonplanData, individualDataIdx, classIdx, teacherIdx, roomIdx, classId, subjectId, teacherId, roomId);

                        if (weekDayAndLessonFound) {
                            return true;
                        }
                    }
                }
            } else {
                // ROOM OK

                bool weekDayAndLessonFound = this->tryAssignWeekDayAndLesson(lessonplanData, individualDataIdx, classIdx, teacherIdx, roomIdx, classId, subjectId, teacherId, roomId);

                if (weekDayAndLessonFound) {
                    return true;
                }
            }
        }

        return false;
    }

    bool LessonplanIndividual::tryAssignWeekDayAndLesson(
            LessonplanData *lessonplanData,
            unsigned short individualDataIdx,
            unsigned short classIdx, unsigned short teacherIdx, unsigned short roomIdx,
            unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId
    ) {
        unsigned short weekDaysCount = lessonplanData->getWeekDaysCount();
        unsigned short lessonsCount = lessonplanData->getLessonsCount();

        vector<unsigned short> lessonsIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getLessonsCount());

        // Iterate through list of lessons
        for (unsigned short lessonIdx = 0; lessonIdx < lessonsCount; lessonIdx++) {
            unsigned short lessonId = lessonsIdsSequence[lessonIdx];

            vector<unsigned short> weekDaysIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getWeekDaysCount());

            // Iterate through list of week days
            for (unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short weekDayId = weekDaysIdsSequence[weekDayIdx];
                unsigned short currentWeekDayIdx = weekDayId - 1;
                unsigned short currentLessonIdx = lessonId - 1;

                if (
                    !this->assignedLessonAndDaysToClasses[currentWeekDayIdx][currentLessonIdx][classId - 1]
                    && !this->assignedLessonAndDaysToTeachers[currentWeekDayIdx][currentLessonIdx][teacherId -1]
                    && !this->assignedLessonAndDaysToRooms[currentWeekDayIdx][currentLessonIdx][roomId - 1]
                ) {
                    // WEEK DAY AND LESSON OK

                    this->assignedLessonAndDaysToClasses[currentWeekDayIdx][currentLessonIdx][classId - 1] = 1;
                    this->assignedLessonAndDaysToTeachers[currentWeekDayIdx][currentLessonIdx][teacherId - 1] = 1;
                    this->assignedLessonAndDaysToRooms[currentWeekDayIdx][currentLessonIdx][roomId - 1] = 1;

                    this->lessonplan[individualDataIdx][0] = weekDayId;
                    this->lessonplan[individualDataIdx][1] = lessonId;
                    this->lessonplan[individualDataIdx][2] = classId;
                    this->lessonplan[individualDataIdx][3] = subjectId;
                    this->lessonplan[individualDataIdx][4] = teacherId;
                    this->lessonplan[individualDataIdx][5] = roomId;

                    return true;
                }
            }
        }

        return false;
    }

    unsigned int LessonplanIndividual::calculateMaxDataCount(LessonplanData *lessonplanData) {
        unsigned int maxDataCount = 0;

        unsigned short classesCount = lessonplanData->getClassesCount();

        for(unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            maxDataCount += static_cast<unsigned short>(lessonplanData->getClassSubjects(classIdx).size());
        }

        return maxDataCount;
    }

    vector<unsigned short> LessonplanIndividual::getRandomIdxsSequence(unsigned short sequenceSize) {
        return LessonplanIndividual::getRandomNumbersSequence(sequenceSize, 0);
    }

    vector<unsigned short> LessonplanIndividual::getRandomIdsSequence(unsigned short sequenceSize) {
        return LessonplanIndividual::getRandomNumbersSequence(sequenceSize, 1);
    }

    vector<unsigned short> LessonplanIndividual::getRandomNumbersSequence(unsigned short sequenceSize, unsigned short lowestNumber) {
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

    vector<vector<unsigned short>> LessonplanIndividual::getLessonplan() {
        return this->lessonplan;
    }

    unsigned int LessonplanIndividual::getMaxDataCount() const {
        return maxDataCount;
    }

}