#include "LessonplanGenAlgorithm.hpp"
#include "LessonplanIndividual.hpp"

#include <utility>


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
        for (unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short classId = classIdx + 1;
            vector<unsigned short> classSubjects = lessonplanData->getClassSubjects(classIdx);

            // CLASS OK

            // Iterate through list of classes subjects
            for (unsigned short subjectIdx = 0; subjectIdx < subjectsCount; subjectIdx++) {
                unsigned short subjectId = classSubjects[subjectIdx];

                // No subjects left for class
                if (!subjectId) {
                    break;
                }

                // SUBJECT OK

                bool teacherFound = this->findPossibleTeacher(lessonplanData, individualDataIdx, classIdx, classId, subjectId);

                if (teacherFound) {
                    individualDataIdx++;
                }
            }
        }

        return this->individual;
    }


    bool LessonplanIndividual::findPossibleTeacher(
            LessonplanData *lessonplanData,
            unsigned short individualDataIdx,
            unsigned short classIdx,
            unsigned short classId, unsigned short subjectId
    ) {
        unsigned short weekDaysCount = lessonplanData->getWeekDaysCount();
        unsigned short lessonsCount = lessonplanData->getLessonsCount();
        unsigned short classesCount = lessonplanData->getClassesCount();
        unsigned short subjectsCount = lessonplanData->getSubjectsCount();
        unsigned short teachersCount = lessonplanData->getTeachersCount();
        unsigned short roomsCount = lessonplanData->getRoomsCount();

        // Iterate through list of teachers
        for (unsigned short teacherIdx = 0; teacherIdx < teachersCount; teacherIdx++) {
            unsigned short teacherId = teacherIdx + 1;
            vector<unsigned short> teacherSubjects = lessonplanData->getTeacherSubjects(teacherIdx);

            // Iterate through list of teachers subjects
            for (unsigned short subjectIdx2 = 0; subjectIdx2 < subjectsCount; subjectIdx2++) {
                unsigned short subjectId2 = teacherSubjects[subjectIdx2];

                // No subjects left for teacher
                if (!subjectId2) {
                    break;
                }

                if (subjectId == subjectId2) {
                    // TEACHER OK

                    bool roomFound = this->findPossibleRoom(lessonplanData, individualDataIdx, classIdx, teacherIdx, classId, subjectId, teacherId);

                    if (roomFound) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool LessonplanIndividual::findPossibleRoom(
            LessonplanData *lessonplanData,
            unsigned short individualDataIdx,
            unsigned short classIdx, unsigned short teacherIdx,
            unsigned short classId, unsigned short subjectId, unsigned short teacherId
    ) {
        unsigned short weekDaysCount = lessonplanData->getWeekDaysCount();
        unsigned short lessonsCount = lessonplanData->getLessonsCount();
        unsigned short classesCount = lessonplanData->getClassesCount();
        unsigned short subjectsCount = lessonplanData->getSubjectsCount();
        unsigned short teachersCount = lessonplanData->getTeachersCount();
        unsigned short roomsCount = lessonplanData->getRoomsCount();

        // Iterate through list of rooms
        for (unsigned short roomIdx = 0; roomIdx < roomsCount; roomIdx++) {
            unsigned short roomId = roomIdx + 1;
            unsigned short roomSubjectsRestrictionStatus = lessonplanData->getRoomSubjectsRestrictionStatus(roomIdx);

            if (roomSubjectsRestrictionStatus) {
                vector<unsigned short> roomSubjects = lessonplanData->getRoomSubjects(roomIdx);

                // Iterate through list of rooms subjects
                for (unsigned short subjectIdx3 = 0; subjectIdx3 < subjectsCount; subjectIdx3++) {
                    unsigned short subjectId3 = roomSubjects[subjectIdx3];

                    // No subjects left for teacher
                    if (!subjectId3) {
                        break;
                    }

                    if (subjectId == subjectId3) {
                        // ROOM OK

                        vector<unsigned short> weekDayIdAndLessonId = this->determinePossibleWeekDayAndLesson(weekDaysCount, lessonsCount, classIdx, teacherIdx, roomIdx);

                        unsigned short weekDayId = weekDayIdAndLessonId[0];
                        unsigned short lessonId = weekDayIdAndLessonId[1];

                        if (weekDayId && lessonId) {
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
            } else {
                // ROOM OK

                vector<unsigned short> weekDayIdAndLessonId = this->determinePossibleWeekDayAndLesson(weekDaysCount, lessonsCount, classIdx, teacherIdx, roomIdx);

                unsigned short weekDayId = weekDayIdAndLessonId[0];
                unsigned short lessonId = weekDayIdAndLessonId[1];

                if (weekDayId && lessonId) {
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

    vector<unsigned short> lessonplans::LessonplanIndividual::determinePossibleWeekDayAndLesson(
            unsigned short weekDaysCount,
            unsigned short lessonsCount,
            unsigned short classIdx,
            unsigned short teacherIdx,
            unsigned short roomIdx
    ) {
        vector<unsigned short> weekDayIdAndLessonId = *new vector<unsigned short>(2);

        // Iterate through list of week days
        for (unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {
            unsigned short weekDayId = weekDayIdx + 1;

            // Iterate through list of lessons
            for (unsigned short lessonIdx = 0; lessonIdx < lessonsCount; lessonIdx++) {
                unsigned short lessonId = lessonIdx + 1;

                if (
                        !this->assignedLessonAndDaysToClasses[weekDayIdx][lessonIdx][classIdx]
                        && !this->assignedLessonAndDaysToTeachers[weekDayIdx][lessonIdx][teacherIdx]
                        && !this->assignedLessonAndDaysToRooms[weekDayIdx][lessonIdx][roomIdx]
                        ) {
                    this->assignedLessonAndDaysToClasses[weekDayIdx][lessonIdx][classIdx] = 1;
                    this->assignedLessonAndDaysToTeachers[weekDayIdx][lessonIdx][teacherIdx] = 1;
                    this->assignedLessonAndDaysToRooms[weekDayIdx][lessonIdx][roomIdx] = 1;

                    weekDayIdAndLessonId[0] = weekDayId;
                    weekDayIdAndLessonId[1] = lessonId;

                    return weekDayIdAndLessonId;
                }
            }
        }

        weekDayIdAndLessonId[0] = 0;
        weekDayIdAndLessonId[1] = 0;

        return weekDayIdAndLessonId;
    }

    vector<vector<unsigned short>> LessonplanIndividual::getIndividual() {
        return this->individual;
    }

}