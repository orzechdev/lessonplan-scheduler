#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    void LessonplanGenAlgorithm::setAlgorithmData(std::vector<int> lessons, std::vector<int> rooms,
                                                  std::vector<int> subjects, std::vector<int> teachers,
                                                  std::vector<int> classes) {
        this->lessons = lessons;
        this->rooms = rooms;
        this->subjects = subjects;
        this->teachers = teachers;
        this->classes = classes;
    }

    void LessonplanGenAlgorithm::initPopulation() {
        this->population = *new std::vector<std::vector<std::vector<int>>>(
                this->populationCount, std::vector<std::vector<int>>(
                        8, std::vector<int>(
                                5
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
        std::vector<std::vector<int>> lessonplan(8, std::vector<int>(5));
        for (long unsigned int i = 0; i < lessonplan.size(); i++) {
            for (long unsigned int j = 0; j < lessonplan[i].size(); j++)
                lessonplan[i][j] = i+j;
        }
        return lessonplan;
    }

}
