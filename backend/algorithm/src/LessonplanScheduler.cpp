#include "../include/algorithm/LessonplanScheduler.hpp"

#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    std::vector<std::vector<int>> LessonplanScheduler::scheduleLessonplan(unsigned short int dayCount, unsigned short int lessonCount,
                                                std::vector<int> rooms, std::vector<int> subjects,
                                                std::vector<int> teachers, std::vector<int> classes) {
        int populationCount = 10;
        int generationNumber = 10;
        float crossoverProb = 0.2;
        float mutationProb = 0.1;

        // In order to have following commented code working, maybe refer to https://stackoverflow.com/questions/52211699/cython-cmake-and-setup-py-python-in-a-subdirectory-compiles-twice

        this->lessonplanGenAlgorithm = new LessonplanGenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb);

        this->lessonplanGenAlgorithm->setAlgorithmData(dayCount, lessonCount, rooms, subjects, teachers, classes);

        bool solutionFound = this->lessonplanGenAlgorithm->run();

        if (solutionFound) {
            return this->lessonplanGenAlgorithm->getLessonplan();
        }

    }
}
