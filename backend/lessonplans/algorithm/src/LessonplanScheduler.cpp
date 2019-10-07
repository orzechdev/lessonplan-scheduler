#include "../include/algorithm/LessonplanScheduler.hpp"

#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    std::vector<std::vector<unsigned short>>
    LessonplanScheduler::scheduleLessonplan(
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> lessonsRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> weekDaysRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> roomsRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> teachersRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> classesRestrictionsForIndividuals,
        std::vector<std::vector<std::vector<std::vector<unsigned short>>>> subjectsRestrictionsForIndividuals
    ) {
        int populationCount = 10;
        int generationNumber = 10;
        float crossoverProb = 0.2;
        float mutationProb = 0.1;

        // In order to have following commented code working, maybe refer to https://stackoverflow.com/questions/52211699/cython-cmake-and-setup-py-python-in-a-subdirectory-compiles-twice

        this->lessonplanGenAlgorithm = new LessonplanGenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb);

        this->lessonplanGenAlgorithm->setAlgorithmData(
                lessonsRestrictionsForIndividuals,
                weekDaysRestrictionsForIndividuals,
                roomsRestrictionsForIndividuals,
                teachersRestrictionsForIndividuals,
                classesRestrictionsForIndividuals,
                subjectsRestrictionsForIndividuals
            );

        bool solutionFound = this->lessonplanGenAlgorithm->run();

        if (solutionFound) {
            return this->lessonplanGenAlgorithm->getLessonplanFromBestIndividual();
        }

    }

}
