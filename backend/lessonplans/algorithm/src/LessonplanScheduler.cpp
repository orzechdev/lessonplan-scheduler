#include "../include/algorithm/LessonplanScheduler.hpp"

#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    std::vector<std::vector<unsigned short>>
    LessonplanScheduler::scheduleLessonplan(
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
        int populationCount = 10;
        int generationNumber = 10;
        float crossoverProb = 0.2;
        float mutationProb = 0.1;

        // In order to have following commented code working, maybe refer to https://stackoverflow.com/questions/52211699/cython-cmake-and-setup-py-python-in-a-subdirectory-compiles-twice

        this->lessonplanGenAlgorithm = new LessonplanGenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb);

        this->lessonplanGenAlgorithm->setAlgorithmData(
                weekDaysCount,
                lessonsCount,
                classesCount,
                subjectsCount,
                teachersCount,
                roomsCount,
                classesSubjectsRestrictionStatus,
                classesSubjects,
                teachersSubjectsRestrictionStatus,
                teachersSubjects,
                roomsSubjectsRestrictionStatus,
                roomsSubjects
            );

        bool solutionFound = this->lessonplanGenAlgorithm->run();

        if (solutionFound) {
            return this->lessonplanGenAlgorithm->getLessonplanFromBestIndividual();
        }

    }

}
