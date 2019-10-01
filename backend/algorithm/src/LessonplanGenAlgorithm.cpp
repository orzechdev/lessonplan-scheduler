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
        this->population = *new std::vector<std::vector<std::vector<unsigned long long>>>(
                this->populationCount, std::vector<std::vector<unsigned long long>>(
                        this->dayCount, std::vector<unsigned long long>(
                                this->lessonCount
                        )
                )
        );

        // TODO: remove or replace following test code
        for (unsigned short i = 0; i < this->dayCount; i++) {
            for (unsigned short j = 0; j < this->lessonCount; j++) {
                this->population[0][i][j] = lessonplans::LessonplanGenAlgorithm::encodeIndividual(0, 0, 2, 15);
            }
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

    unsigned long long LessonplanGenAlgorithm::encodeIndividual(unsigned short room, unsigned short subject,
                                             unsigned short teacher, unsigned short classItem) {
        unsigned long long individual = (
                ((unsigned long long) classItem << 48u) // Set fourth byte as class
                | ((unsigned long long) teacher << 32u) // Set third byte as teacher
                | ((unsigned long long) subject << 16u) // Set second byte as subject
                | (unsigned long long) room // Set first byte as room
        );

        return individual;
    }

    std::vector<unsigned short> LessonplanGenAlgorithm::decodeIndividual(unsigned long long individual) {
        std::vector<unsigned short> data = *new std::vector<unsigned short>(
                4 // Four different data encoded -> room, subject, teacher, class
        );

        data[0] = (individual & 0xFFu); // Extract first byte as room
        data[1] = ((individual >> 16u) & 0xFFu); // Extract second byte as subject
        data[2] = ((individual >> 32u) & 0xFFu); // Extract third byte as teacher
        data[3] = ((individual >> 48u) & 0xFFu); // Extract fourth byte as class

        return data;
    }

    std::vector<std::vector<unsigned long long>> LessonplanGenAlgorithm::getBestIndividual() {
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

        std::vector<std::vector<unsigned long long>> bestIndividual = this->getBestIndividual();
        unsigned short bestIndividualDayCount = bestIndividual.size();
        unsigned short bestIndividualLessonCount = bestIndividual[0].size();

        for (unsigned short i = 0; i < bestIndividualDayCount; i++) {
            std::vector<unsigned long long> bestIndividualValues = bestIndividual[i];
            for (unsigned short j = 0; j < bestIndividualLessonCount; j++) {
                lessonplan[i][j] = lessonplans::LessonplanGenAlgorithm::decodeIndividual(bestIndividualValues[j]);
            }
        }

        return lessonplan;
    }

}
