#include "../include/algorithm/LessonplanScheduler.hpp"

//#include "LessonplanGenAlgorithm.hpp"

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

        // In order to have following commented code working, maybe refer to https://stackoverflow.com/questions/52211699/cython-cmake-and-setup-py-python-in-a-subdirectory-compiles-twice

//        this->lessonplanGenAlgorithm = new LessonplanGenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb);
//
//        this->lessonplanGenAlgorithm->setAlgorithmData(lessons, rooms, subjects, teachers, classes);
//
//        bool solutionFound = this->lessonplanGenAlgorithm->run();
//
//        if (solutionFound) {
//            return this->lessonplanGenAlgorithm->getLessonplan();
//        }

        // TEST
        std::vector<std::vector<int>> lessonplan(8, std::vector<int>(5));
        for (int i = 0; i < lessonplan.size(); i++) {
            for (int j = 0; j < lessonplan[i].size(); j++)
                lessonplan[i][j] = i+j;
        }
        return lessonplan;
    }
}
