#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    void LessonplanGenAlgorithm::setAlgorithmData(unsigned short dayCount, unsigned short lessonCount,
                                                  std::vector<unsigned short> rooms, std::vector<unsigned short> subjects,
                                                  std::vector<unsigned short> teachers, std::vector<unsigned short> classes) {
        this->dayCount = dayCount;
        this->lessonCount = lessonCount;
        this->rooms = rooms;
        this->subjects = subjects;
        this->teachers = teachers;
        this->classes = classes;
    }

    void LessonplanGenAlgorithm::initPopulation() {
        this->population = *new std::vector<std::vector<std::vector<unsigned long int>>>(
                this->populationCount, std::vector<std::vector<unsigned long int>>(
                        this->dayCount, std::vector<unsigned long int>(
                                this->lessonCount
                        )
                )
        );
    }

    void LessonplanGenAlgorithm::crossover() {

    }

    void LessonplanGenAlgorithm::mutate() {

    }

    void LessonplanGenAlgorithm::evaluate() {

    }

    void LessonplanGenAlgorithm::select() {

    }

    unsigned long int LessonplanGenAlgorithm::encodeIndividual(unsigned short room, unsigned short subject,
                                             unsigned short teacher, unsigned short classItem) {
        // TODO: ...

        return 0;
    }

    std::vector<unsigned short> LessonplanGenAlgorithm::decodeIndividual(unsigned long int individual) {
        std::vector<unsigned short> data = *new std::vector<unsigned short>(
                4 // Four different data encoded -> room, subject, teacher, class
        );

        data[0] = (individual & 0xFFu); // Extract first byte as room
        data[1] = ((individual >> 8u) & 0xFFu); // Extract second byte as subject
        data[2] = ((individual >> 16u) & 0xFFu); // Extract third byte as teacher
        data[3] = ((individual >> 24u) & 0xFFu); // Extract fourth byte as class

        return data;
    }

    std::vector<std::vector<unsigned long int>> LessonplanGenAlgorithm::getBestIndividual() {
        return this->population[0];
    }

    std::vector<std::vector<std::vector<unsigned short>>> LessonplanGenAlgorithm::getLessonplanFromBestIndividual() {
        std::vector<std::vector<std::vector<unsigned short>>> lessonplan = *new std::vector<std::vector<std::vector<unsigned short>>>(
                this->dayCount, std::vector<std::vector<unsigned short>>(
                        this->lessonCount, std::vector<unsigned short>(
                                4 // Four different data encoded -> room, subject, teacher, class
                        )
                )
        );

        std::vector<std::vector<unsigned long int>> bestIndividual = this->getBestIndividual();
        unsigned short bestIndividualDayCount = bestIndividual.size();
        unsigned short bestIndividualLessonCount = bestIndividual[0].size();

        for (unsigned short i = 0; i < bestIndividualDayCount; i++) {
            for (unsigned short j = 0; j < bestIndividualLessonCount; j++) {
                unsigned long int testIndividualValue = 4026597120+i+j; // TODO: instead of testValue, use bestIndividual[i][j]
                lessonplan[i][j] = this->decodeIndividual(testIndividualValue);
            }
        }

        return lessonplan;
    }

}
