#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    void LessonplanGenAlgorithm::setAlgorithmData(unsigned short classCount, unsigned short dayCount, unsigned short lessonCount,
                                                  std::vector<unsigned short> rooms, //std::vector<unsigned short> subjects,
                                                  std::vector<unsigned short> teachers, std::vector<std::vector<std::vector<unsigned short>>> classesSubjectsIdsWithClassesSubjectsHours) {
        this->classCount = classCount;
        this->dayCount = dayCount;
        this->lessonCount = lessonCount;
        this->rooms = rooms;
//        this->subjects = subjects;
        this->teachers = teachers;
        this->classesSubjectsIdsWithClassesSubjectsHours = classesSubjectsIdsWithClassesSubjectsHours;
    }

    void LessonplanGenAlgorithm::setAlgorithmConstraints(std::vector<bool> roomsExclusiveAssignments,
                                                         std::vector<std::vector<unsigned short>> subjectsRooms,
                                                         std::vector<std::vector<unsigned short>> teachersSubjects) {
        this->roomsExclusiveAssignments = roomsExclusiveAssignments;
        this->subjectsRooms = subjectsRooms;
        this->teachersSubjects = teachersSubjects;
    }

    void LessonplanGenAlgorithm::initPopulation() {
//        this->population = *new std::vector<std::vector<std::vector<std::vector<unsigned long long>>>>(
//                this->populationCount, std::vector<std::vector<std::vector<unsigned long long>>>(
//                        this->classCount, std::vector<std::vector<unsigned long long>>(
//                                this->dayCount, std::vector<unsigned long long>(
//                                        this->lessonCount
//                                )
//                        )
//                )
//        );
        this->population = *new std::vector<std::vector<std::vector<std::vector<std::vector<unsigned short>>>>>(
                this->populationCount, std::vector<std::vector<std::vector<std::vector<unsigned short>>>>(
                        this->classCount, std::vector<std::vector<std::vector<unsigned short>>>(
                                this->dayCount, std::vector<std::vector<unsigned short>>(
                                        this->lessonCount, std::vector<unsigned short>(
                                                3 // Three different data -> room, subject, teacher
                                        )
                                )
                        )
                )
        );

        /*
         * TODO: THE FOLLOWING CODE IS ONLY DONE FOR THE BEST INDIVIDUAL! IT SHOULD BE DONE TO ALL POPULATION!!!
         */

        this->teachersAssignedToDaysAndLessons = *new std::vector<std::vector<std::vector<std::vector<unsigned short>>>>(
                this->populationCount, std::vector<std::vector<std::vector<unsigned short>>>(
                        this->dayCount, std::vector<std::vector<unsigned short>>(
                                this->lessonCount, std::vector<unsigned short>(
                                        this->teachers.size() // Max different teachers to be assigned
                                )
                        )
                )
        );
        this->roomsAssignedToDaysAndLessons = *new std::vector<std::vector<std::vector<std::vector<unsigned short>>>>(
                this->populationCount, std::vector<std::vector<std::vector<unsigned short>>>(
                        this->dayCount, std::vector<std::vector<unsigned short>>(
                                this->lessonCount, std::vector<unsigned short>(
                                        this->rooms.size() // Max different rooms to be assigned
                                )
                        )
                )
        );

        for (unsigned short i = 0; i < this->classCount; i++) {
            std::vector<std::vector<unsigned short>> subjectsIdsWithSubjectsHours = this->classesSubjectsIdsWithClassesSubjectsHours[i];
            long unsigned int currentClassSubject = 0;
            // Class doesn't have any subject - proceed with another class
            if (subjectsIdsWithSubjectsHours.empty()) {
                continue;
            }
            // Take the first subject for class and remember how many hours it has to have
            int leftClassSubjectHours = subjectsIdsWithSubjectsHours[currentClassSubject][1];
            // Start from first lesson and iterate over all days, then proceed with second lesson, third, and so on,
            // as it is good to start lessons from morning and spread them throughout all days
            for (unsigned short j = 0; j < this->lessonCount; j++) {
                for (unsigned short k = 0; k < this->dayCount; k++) {
                    // First check if there are some subject hours left to insert into the lessonplan
                    while (leftClassSubjectHours <= 0) {
                        // If no more subject hours left, try to take another subject if available
                        currentClassSubject++;
                        if (currentClassSubject >= subjectsIdsWithSubjectsHours.size()) {
                            // If no more subjects, break to proceed with another class
                            break;
                        } else {
                            // If another subject is present, remember how many hours it has to have
                            leftClassSubjectHours = subjectsIdsWithSubjectsHours[currentClassSubject][1];
                        }
                    }
                    // If no more subjects, break to proceed with another class
                    if (currentClassSubject >= subjectsIdsWithSubjectsHours.size()) {
                        break;
                    }
                    this->population[0][i][k][j][0] = subjectsIdsWithSubjectsHours[currentClassSubject][0]; // subject
                    // Subject hour was assigned, thus decrease number of left hours to assign
                    leftClassSubjectHours--;

                    this->population[0][i][k][j][1] = 0; // TODO teacher - maybe utilize this->teachersAssignedToDaysAndLessons
                    this->population[0][i][k][j][2] = 0; // TODO room - maybe utilize this->roomsAssignedToDaysAndLessons
                }
                // If no more subjects, break to proceed with another class
                if (currentClassSubject >= subjectsIdsWithSubjectsHours.size()) {
                    break;
                }
            }
        }

//        for (unsigned short i = 0; i < this->classCount; i++) {
//            for (unsigned short j = 0; j < this->dayCount; j++) {
//                for (unsigned short k = 0; k < this->lessonCount; k++) {
//                    this->population[0][i][j][k] = lessonplans::LessonplanGenAlgorithm::encodeIndividualLesson(0, 0, 2, 15);
//                }
//            }
//        }

//        for (unsigned short i = 0; i < this->classCount; i++) {
//            for (unsigned short j = 0; j < this->lessonCount; j++) {
//                for (unsigned short k = 0; k < this->dayCount; k++) {
//                    unsigned short classSubjectHours = 0;
//                    do {
//                        classSubjectHours = this->initLesson(i, (j * this->lessonCount) + k, selectedRoomsForDays[j]);
//                    } while (classSubjectHours > 0);
//                }
//            }
//        }
//
//
//
//        std::vector<std::vector<unsigned short>> selectedRoomsForDays;
//        for (unsigned short i = 0; i < this->lessonCount; i++) {
//            for (unsigned short j = 0; j < this->dayCount; j++) {
//                unsigned short classSubjectHours = 0;
//                do {
//                    classSubjectHours = this->initLesson((i * this->lessonCount) + j, selectedRoomsForDays[j]);
//                } while (classSubjectHours > 0);
//            }
//        }
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

    std::vector<std::vector<std::vector<std::vector<unsigned short>>>> LessonplanGenAlgorithm::getBestIndividual() {
        return this->population[0];
    }

    std::vector<std::vector<std::vector<std::vector<unsigned short>>>> LessonplanGenAlgorithm::getLessonplanFromBestIndividual() {
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
