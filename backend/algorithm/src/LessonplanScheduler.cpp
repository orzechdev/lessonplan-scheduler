#include "../include/algorithm/LessonplanScheduler.hpp"

#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    std::vector<std::vector<std::vector<unsigned short>>> LessonplanScheduler::scheduleLessonplan(unsigned short dayCount, unsigned short lessonCount,
                                                std::vector<unsigned short> rooms, std::vector<unsigned short> subjects,
                                                std::vector<unsigned short> teachers, std::vector<unsigned short> classes) {
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
