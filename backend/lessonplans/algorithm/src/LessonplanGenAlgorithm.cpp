#include "LessonplanGenAlgorithm.hpp"

#include <utility>
#include <climits>

namespace lessonplans {

    void LessonplanGenAlgorithm::setAlgorithmData(
        unsigned short weekDaysCount,
        unsigned short lessonsCount,
        unsigned short classesCount,
        unsigned short subjectsCount,
        unsigned short teachersCount,
        unsigned short roomsCount,
        std::vector<unsigned short> classesSubjectsRestrictionStatus,
        std::vector<std::vector<unsigned short>> classesSubjects,
        std::vector<unsigned short> teachersSubjectsRestrictionStatus,
        std::vector<std::vector<unsigned short>> teachersSubjects,
        std::vector<unsigned short> roomsSubjectsRestrictionStatus,
        std::vector<std::vector<unsigned short>> roomsSubjects
    ) {
        this->weekDaysCount = weekDaysCount;
        this->lessonsCount = lessonsCount;
        this->classesCount = classesCount;
        this->subjectsCount = subjectsCount;
        this->teachersCount = teachersCount;
        this->roomsCount = roomsCount;
        this->classesSubjectsRestrictionStatus = std::move(classesSubjectsRestrictionStatus);
        this->classesSubjects = std::move(classesSubjects);
        this->teachersSubjectsRestrictionStatus = std::move(teachersSubjectsRestrictionStatus);
        this->teachersSubjects = std::move(teachersSubjects);
        this->roomsSubjectsRestrictionStatus = std::move(roomsSubjectsRestrictionStatus);
        this->roomsSubjects = std::move(roomsSubjects);
    }

    std::vector<unsigned short> LessonplanGenAlgorithm::getRandomTakingSequence(unsigned short sequenceSize) {
        // TODO: ... https://stackoverflow.com/questions/20734774/random-array-generation-with-no-duplicates

        return std::vector<unsigned short>();
    }

    void LessonplanGenAlgorithm::initPopulation() {
        int maxDataCount = this->classesCount * this->subjectsCount;

        short dataTypes = 6;

        this->population = *new std::vector<std::vector<std::vector<unsigned short>>>(
                this->populationCount, std::vector<std::vector<unsigned short>>(
                        maxDataCount, std::vector<unsigned short>(
                                dataTypes
                        )
                )
        );
        this->populationAssignedLessonAndDaysToClasses = *new std::vector<std::vector<std::vector<std::vector<unsigned short>>>>(
                this->populationCount, std::vector<std::vector<std::vector<unsigned short>>>(
                        this->weekDaysCount, std::vector<std::vector<unsigned short>>(
                                this->lessonsCount, std::vector<unsigned short>(
                                        this->classesCount
                                )
                        )
                )
        );
        this->populationAssignedLessonAndDaysToTeachers = *new std::vector<std::vector<std::vector<std::vector<unsigned short>>>>(
                this->populationCount, std::vector<std::vector<std::vector<unsigned short>>>(
                        this->weekDaysCount, std::vector<std::vector<unsigned short>>(
                                this->lessonsCount, std::vector<unsigned short>(
                                        this->teachersCount
                                )
                        )
                )
        );
        this->populationAssignedLessonAndDaysToRooms = *new std::vector<std::vector<std::vector<std::vector<unsigned short>>>>(
                this->populationCount, std::vector<std::vector<std::vector<unsigned short>>>(
                        this->weekDaysCount, std::vector<std::vector<unsigned short>>(
                                this->lessonsCount, std::vector<unsigned short>(
                                        this->roomsCount
                                )
                        )
                )
        );

        for (unsigned int i = 0; i < this->populationCount; i++) {
            this->population[i] = this->initIndividual(i);
        }


    }

    std::vector<std::vector<unsigned short>> LessonplanGenAlgorithm::initIndividual(unsigned short individualIndex) {
        std::vector<std::vector<unsigned short>> individual = this->population[individualIndex];
        unsigned short individualDataIdx = 0;
        bool nextClassSubjectRequired;

        // Iterate through list of classes
        for (unsigned short classIdx = 0; classIdx < this->classesCount; classIdx++) {
            unsigned short classId = classIdx + 1;
            std::vector<unsigned short> classSubjects = this->classesSubjects[classIdx];

            // CLASS OK

            // Iterate through list of classes subjects
            for (unsigned short subjectIdx = 0; subjectIdx < this->subjectsCount; subjectIdx++) {
                nextClassSubjectRequired = false;

                unsigned short subjectId = classSubjects[subjectIdx];

                // No subjects left for class
                if (!subjectId) {
                    break;
                }

                // SUBJECT OK

                // Iterate through list of teachers
                for (unsigned short teacherIdx = 0; teacherIdx < this->teachersCount; teacherIdx++) {
                    unsigned short teacherId = teacherIdx + 1;
                    std::vector<unsigned short> teacherSubjects = this->teachersSubjects[teacherIdx];

                    // Iterate through list of teachers subjects
                    for (unsigned short subjectIdx2 = 0; subjectIdx2 < this->subjectsCount; subjectIdx2++) {
                        unsigned short subjectId2 = teacherSubjects[subjectIdx2];

                        // No subjects left for teacher
                        if (!subjectId2) {
                            break;
                        }

                        if (subjectId == subjectId2) {
                            // TEACHER OK

                            // Iterate through list of rooms
                            for (unsigned short roomIdx = 0; roomIdx < this->roomsCount; roomIdx++) {
                                unsigned short roomId = roomIdx + 1;
                                unsigned short roomSubjectsRestrictionStatus = this->roomsSubjectsRestrictionStatus[roomIdx];

                                if (roomSubjectsRestrictionStatus) {
                                    std::vector<unsigned short> roomSubjects = this->roomsSubjects[roomIdx];

                                    // Iterate through list of rooms subjects
                                    for (unsigned short subjectIdx3 = 0; subjectIdx3 < this->subjectsCount; subjectIdx3++) {
                                        unsigned short subjectId3 = roomSubjects[subjectIdx3];

                                        // No subjects left for teacher
                                        if (!subjectId3) {
                                            break;
                                        }

                                        if (subjectId == subjectId3) {
                                            // ROOM OK

                                            std::vector<unsigned short> weekDayIdAndLessonId = this->initIndividualSetWeekDayAndLesson(individualIndex, classIdx, teacherIdx, roomIdx);

                                            unsigned short weekDayId = weekDayIdAndLessonId[0];
                                            unsigned short lessonId = weekDayIdAndLessonId[1];

                                            if (weekDayId && lessonId) {
                                                individual[individualDataIdx][0] = weekDayId;
                                                individual[individualDataIdx][1] = lessonId;
                                                individual[individualDataIdx][2] = classId;
                                                individual[individualDataIdx][3] = subjectId;
                                                individual[individualDataIdx][4] = teacherId;
                                                individual[individualDataIdx][5] = roomId;

                                                individualDataIdx++;
                                                nextClassSubjectRequired = true;
                                            }
                                        }

                                        if (nextClassSubjectRequired) {
                                            break;
                                        }
                                    }
                                } else {
                                    // ROOM OK

                                    std::vector<unsigned short> weekDayIdAndLessonId = this->initIndividualSetWeekDayAndLesson(individualIndex, classIdx, teacherIdx, roomIdx);

                                    unsigned short weekDayId = weekDayIdAndLessonId[0];
                                    unsigned short lessonId = weekDayIdAndLessonId[1];

                                    if (weekDayId && lessonId) {
                                        individual[individualDataIdx][0] = weekDayId;
                                        individual[individualDataIdx][1] = lessonId;
                                        individual[individualDataIdx][2] = classId;
                                        individual[individualDataIdx][3] = subjectId;
                                        individual[individualDataIdx][4] = teacherId;
                                        individual[individualDataIdx][5] = roomId;

                                        individualDataIdx++;
                                        nextClassSubjectRequired = true;
                                    }
                                }

                                if (nextClassSubjectRequired) {
                                    break;
                                }
                            }
                        }

                        if (nextClassSubjectRequired) {
                            break;
                        }
                    }

                    if (nextClassSubjectRequired) {
                        break;
                    }
                }
            }
        }

        return individual;
    }

    std::vector<unsigned short> LessonplanGenAlgorithm::initIndividualSetWeekDayAndLesson(unsigned short individualIndex, unsigned short classIdx, unsigned short teacherIdx, unsigned short roomIdx) {
        std::vector<unsigned short> weekDayIdAndLessonId = *new std::vector<unsigned short>(2);

        // Iterate through list of week days
        for (unsigned short weekDayIdx = 0; weekDayIdx < this->weekDaysCount; weekDayIdx++) {
            unsigned short weekDayId = weekDayIdx + 1;

            // Iterate through list of lessons
            for (unsigned short lessonIdx = 0; lessonIdx < this->lessonsCount; lessonIdx++) {
                unsigned short lessonId = lessonIdx + 1;

                if (
                    !this->populationAssignedLessonAndDaysToClasses[individualIndex][weekDayIdx][lessonIdx][classIdx]
                    && !this->populationAssignedLessonAndDaysToTeachers[individualIndex][weekDayIdx][lessonIdx][teacherIdx]
                    && !this->populationAssignedLessonAndDaysToRooms[individualIndex][weekDayIdx][lessonIdx][roomIdx]
                ) {
                    this->populationAssignedLessonAndDaysToClasses[individualIndex][weekDayIdx][lessonIdx][classIdx] = 1;
                    this->populationAssignedLessonAndDaysToTeachers[individualIndex][weekDayIdx][lessonIdx][teacherIdx] = 1;
                    this->populationAssignedLessonAndDaysToRooms[individualIndex][weekDayIdx][lessonIdx][roomIdx] = 1;

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

    void LessonplanGenAlgorithm::crossover() {

    }

    void LessonplanGenAlgorithm::mutate() {

    }

    void LessonplanGenAlgorithm::evaluate() {

    }

    void LessonplanGenAlgorithm::select() {

    }

    std::vector<unsigned short> LessonplanGenAlgorithm::initLessons(unsigned short classIndex, unsigned int lessonIndex, std::vector<unsigned short> alreadySelectedRooms) {
//        unsigned short classesCount = this->classes.size();
//
//        for (unsigned short i = 0; i < classesCount; i++) {
//            unsigned short selectedClass = this->classes[i]; // TO USE
//            std::vector<std::vector<unsigned short>> classSubjectsWithHours = this->classesSubjectsWithHours[i];
//            unsigned short classSubjectsCount = classSubjectsWithHours.size();
//
//            for (unsigned short j = 0; j < classSubjectsCount; j++) {
//                unsigned short selectedSubject = classSubjectsWithHours[j][0]; // TO USE
//                unsigned short classSubjectHours = classSubjectsWithHours[j][1];
//
//                // find room
//
//                // find teacher
//
//                for (unsigned short k = 0; k < classSubjectHours; k++) {
//
//                }
//            }
//        }
    }

//    unsigned long long LessonplanGenAlgorithm::encodeIndividualLesson(unsigned short room, unsigned short subject,
//                                             unsigned short teacher, unsigned short classItem) {
//        unsigned long long individualLesson = (
//                ((unsigned long long) classItem << 48u) // Set fourth byte as class
//                | ((unsigned long long) teacher << 32u) // Set third byte as teacher
//                | ((unsigned long long) subject << 16u) // Set second byte as subject
//                | (unsigned long long) room // Set first byte as room
//        );
//
//        return individualLesson;
//    }
//
//    std::vector<unsigned short> LessonplanGenAlgorithm::decodeIndividualLesson(unsigned long long individual) {
//        std::vector<unsigned short> individualLessonData = *new std::vector<unsigned short>(
//                4 // Four different data encoded -> room, subject, teacher, class
//        );
//
//        individualLessonData[0] = (individual & 0xFFu); // Extract first byte as room
//        individualLessonData[1] = ((individual >> 16u) & 0xFFu); // Extract second byte as subject
//        individualLessonData[2] = ((individual >> 32u) & 0xFFu); // Extract third byte as teacher
//        individualLessonData[3] = ((individual >> 48u) & 0xFFu); // Extract fourth byte as class
//
//        return individualLessonData;
//    }

    std::vector<std::vector<unsigned short>> LessonplanGenAlgorithm::getBestIndividual() {
        return this->population[0];
    }

    std::vector<std::vector<unsigned short>> LessonplanGenAlgorithm::getLessonplanFromBestIndividual() {
//        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> lessonplan = *new std::vector<std::vector<std::vector<std::vector<unsigned short>>>>(
//                this->classCount, std::vector<std::vector<std::vector<unsigned short>>>(
//                        this->dayCount, std::vector<std::vector<unsigned short>>(
//                                this->lessonCount, std::vector<unsigned short>(
//                                        4 // Four different data encoded -> room, subject, teacher, class
//                                )
//                        )
//                )
//        );
//
//        std::vector<std::vector<std::vector<unsigned long long>>> bestIndividual = this->getBestIndividual();
//        unsigned short bestIndividualClassCount = bestIndividual.size();
//        unsigned short bestIndividualDayCount = bestIndividual[0].size();
//        unsigned short bestIndividualLessonCount = bestIndividual[0][0].size();
//
//        for (unsigned short i = 0; i < bestIndividualClassCount; i++) {
//            std::vector<std::vector<unsigned long long>> bestIndividualClass = bestIndividual[i];
//            for (unsigned short j = 0; j < bestIndividualDayCount; j++) {
//                std::vector<unsigned long long> bestIndividualDay = bestIndividualClass[j];
//                for (unsigned short k = 0; k < bestIndividualLessonCount; k++) {
//                    lessonplan[i][j][k] = lessonplans::LessonplanGenAlgorithm::decodeIndividualLesson(bestIndividualDay[k]);
//                }
//            }
//        }
//
//        return lessonplan;
        return this->getBestIndividual();
    }

}
