#include "LessonplanGenAlgorithm.hpp"
#include "LessonplanIndividual.hpp"

#include <utility>
#include <random>
#include <algorithm>
#include <chrono>


namespace lessonplans {

    vector<vector<unsigned short>> LessonplanIndividual::initLessonplan(LessonplanData* lessonplanData) {
        unsigned short weekDaysCount = lessonplanData->getWeekDaysCount();
        unsigned short lessonsCount = lessonplanData->getLessonsCount();
        unsigned short classesCount = lessonplanData->getClassesCount();
        unsigned short subjectsCount = lessonplanData->getSubjectsCount();
        unsigned short teachersCount = lessonplanData->getTeachersCount();
        unsigned short roomsCount = lessonplanData->getRoomsCount();

        this->maxDataCount = classesCount * subjectsCount;

        this->individual = *new vector<vector<unsigned short>>(
                this->maxDataCount, vector<unsigned short>(
                        LessonplanIndividual::dataTypes
                )
        );

        this->initRandomIdsSequencesForData(lessonplanData);

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

        // Iterate through list of classes
        for (unsigned short classIdx = 0; classIdx < classesCount; classIdx++) { // TODO: Change for iteration on ****IdsSequence vector
            unsigned short classId = classIdx + 1;
            vector<unsigned short> classSubjects = lessonplanData->getClassSubjects(classIdx);

            // CLASS OK

            // Iterate through list of classes subjects
            for (unsigned short subjectIdx = 0; subjectIdx < subjectsCount; subjectIdx++) { // TODO: Change for iteration on ****IdsSequence vector
                unsigned short subjectId = classSubjects[subjectIdx];

                // No subjects left for class
                if (!subjectId) {
                    break;
                }

                // SUBJECT OK

                bool teacherFound = this->tryAssignTeacher(lessonplanData, individualDataIdx, classIdx, classId, subjectId);

                if (teacherFound) {
                    individualDataIdx++;
                }
            }
        }

        return this->individual;
    }

    bool LessonplanIndividual::tryAssignTeacher(
            LessonplanData *lessonplanData,
            unsigned short individualDataIdx,
            unsigned short classIdx,
            unsigned short classId, unsigned short subjectId
    ) {
        unsigned short subjectsCount = lessonplanData->getSubjectsCount();
        unsigned short teachersCount = lessonplanData->getTeachersCount();

        // Iterate through list of teachers
        for (unsigned short teacherIdx = 0; teacherIdx < teachersCount; teacherIdx++) { // TODO: Change for iteration on ****IdsSequence vector
            unsigned short teacherId = teacherIdx + 1;
            vector<unsigned short> teacherSubjects = lessonplanData->getTeacherSubjects(teacherIdx);

            // Iterate through list of teachers subjects
            for (unsigned short subjectIdx2 = 0; subjectIdx2 < subjectsCount; subjectIdx2++) { // TODO: MAYBE Change for iteration on ****IdsSequence vector
                unsigned short subjectId2 = teacherSubjects[subjectIdx2];

                // No subjects left for teacher
                if (!subjectId2) {
                    break;
                }

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

        // Iterate through list of rooms
        for (unsigned short roomIdx = 0; roomIdx < roomsCount; roomIdx++) { // TODO: Change for iteration on ****IdsSequence vector
            unsigned short roomId = roomIdx + 1;
            unsigned short roomSubjectsRestrictionStatus = lessonplanData->getRoomSubjectsRestrictionStatus(roomIdx);

            if (roomSubjectsRestrictionStatus) {
                vector<unsigned short> roomSubjects = lessonplanData->getRoomSubjects(roomIdx);

                // Iterate through list of rooms subjects
                for (unsigned short subjectIdx3 = 0; subjectIdx3 < subjectsCount; subjectIdx3++) { // TODO: MAYBE Change for iteration on ****IdsSequence vector
                    unsigned short subjectId3 = roomSubjects[subjectIdx3];

                    // No subjects left for teacher
                    if (!subjectId3) {
                        break;
                    }

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

        // Iterate through list of week days
        for (unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) { // TODO: Change for iteration on ****IdsSequence vector
            unsigned short weekDayId = weekDayIdx + 1;

            // Iterate through list of lessons
            for (unsigned short lessonIdx = 0; lessonIdx < lessonsCount; lessonIdx++) { // TODO: Change for iteration on ****IdsSequence vector
                unsigned short lessonId = lessonIdx + 1;

                if (
                    !this->assignedLessonAndDaysToClasses[weekDayIdx][lessonIdx][classIdx]
                    && !this->assignedLessonAndDaysToTeachers[weekDayIdx][lessonIdx][teacherIdx]
                    && !this->assignedLessonAndDaysToRooms[weekDayIdx][lessonIdx][roomIdx]
                ) {
                    // WEEK DAY AND LESSON OK

                    this->assignedLessonAndDaysToClasses[weekDayIdx][lessonIdx][classIdx] = 1;
                    this->assignedLessonAndDaysToTeachers[weekDayIdx][lessonIdx][teacherIdx] = 1;
                    this->assignedLessonAndDaysToRooms[weekDayIdx][lessonIdx][roomIdx] = 1;

                    this->individual[individualDataIdx][0] = weekDayId;
                    this->individual[individualDataIdx][1] = lessonId;
                    this->individual[individualDataIdx][2] = classId;
                    this->individual[individualDataIdx][3] = subjectId;
                    this->individual[individualDataIdx][4] = teacherId;
                    this->individual[individualDataIdx][5] = roomId;

                    return true;
                }
            }
        }

        return false;
    }

    void LessonplanIndividual::initRandomIdsSequencesForData(LessonplanData* lessonplanData) {
        this->weekDaysIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getWeekDaysCount());
        this->lessonsIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getLessonsCount());
        this->classesIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getClassesCount());
        this->subjectsIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getSubjectsCount());
        this->teachersIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getTeachersCount());
        this->roomsIdsSequence = LessonplanIndividual::getRandomIdsSequence(lessonplanData->getRoomsCount());
    }

    vector<unsigned short> LessonplanIndividual::getRandomIdsSequence(unsigned short sequenceSize) {
        // Init vector with required size
        vector<unsigned short> sequence = *new vector<unsigned short>(
                sequenceSize
        );

        // Populate vector with increasing numbers
        std::iota(std::begin(sequence), std::end(sequence), 1);

        // Init random engine with unusual seed
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine randomEngine(seed);

        // Shuffle numbers in vector with random engine to obtain theirs random distribution
        std::shuffle(std::begin(sequence), std::end(sequence), randomEngine);

        return sequence;
    }

    vector<vector<unsigned short>> LessonplanIndividual::getIndividual() {
        return this->individual;
    }

}