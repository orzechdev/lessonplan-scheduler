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

        this->population = *new std::vector<LessonplanIndividual>(
                this->populationCount
        );

        for (int i = 0; i < this->populationCount; i++) {
            LessonplanIndividual lessonplanIndividual = *new LessonplanIndividual();

            lessonplanIndividual.initLessonplan(
                    this->weekDaysCount,
                    this->lessonsCount,
                    this->classesCount,
                    this->subjectsCount,
                    this->teachersCount,
                    this->roomsCount,
                    this->classesSubjects,
                    this->teachersSubjects,
                    this->roomsSubjectsRestrictionStatus,
                    this->roomsSubjects
            );

            this->population[i] = lessonplanIndividual;
        }
    }

    void LessonplanGenAlgorithm::crossover() {

    }

    void LessonplanGenAlgorithm::mutate() {

    }

    void LessonplanGenAlgorithm::evaluate() {

    }

    void LessonplanGenAlgorithm::select() {

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
        return this->population[0].getIndividual();
    }

    std::vector<std::vector<unsigned short>> LessonplanGenAlgorithm::getLessonplanFromBestIndividual() {
        return this->getBestIndividual();
    }

}
