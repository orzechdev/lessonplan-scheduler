#include "../include/algorithm/LessonplanScheduler.h"

#include "LessonplanGenAlgorithm.h"

namespace lessonplans {
    LessonplanScheduler::LessonplanScheduler() {}

    LessonplanScheduler::~LessonplanScheduler() {}

    std::vector<std::vector<int>> LessonplanScheduler::scheduleLessonplan(std::vector<int> lessons, std::vector<int> rooms,
                                                std::vector<int> subjects, std::vector<int> teachers,
                                                std::vector<int> classes) {
        int populationCount = 10;
        int generationNumber = 10;
        float crossoverProb = 0.2;
        float mutationProb = 0.1;

        this->lessonplanGenAlgorithm = new LessonplanGenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb);

        this->lessonplanGenAlgorithm->setAlgorithmData(lessons, rooms, subjects, teachers, classes);

        bool solutionFound = this->lessonplanGenAlgorithm->run();

        if (solutionFound) {
            return this->lessonplanGenAlgorithm->getLessonplan();
        }
    }
}
