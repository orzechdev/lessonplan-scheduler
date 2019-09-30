#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    void LessonplanGenAlgorithm::setAlgorithmData(unsigned short int dayCount, unsigned short int lessonCount,
                                                  std::vector<int> rooms, std::vector<int> subjects,
                                                  std::vector<int> teachers, std::vector<int> classes) {
        this->dayCount = dayCount;
        this->lessonCount = lessonCount;
        this->rooms = rooms;
        this->subjects = subjects;
        this->teachers = teachers;
        this->classes = classes;
    }

    void LessonplanGenAlgorithm::initPopulation() {
        this->population = *new std::vector<std::vector<std::vector<int>>>(
                this->populationCount, std::vector<std::vector<int>>(
                        this->dayCount, std::vector<int>(
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

    std::vector<std::vector<int>> LessonplanGenAlgorithm::getLessonplan() {
//        std::vector<std::vector<int>> lessonplan(8, std::vector<int>(5));
        for (long unsigned int i = 0; i < this->population[0].size(); i++) {
            for (long unsigned int j = 0; j < this->population[0][i].size(); j++)
                this->population[0][i][j] = i+j;
        }
        return this->population[0];
    }

}
