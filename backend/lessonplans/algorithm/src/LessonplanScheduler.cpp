#include "../include/algorithm/LessonplanScheduler.hpp"

#include <utility>

#include "LessonplanGenAlgorithm.hpp"
#include "LessonplanData.hpp"

namespace lessonplans {

    vector<vector<unsigned short>> LessonplanScheduler::scheduleLessonplan(
            unsigned short weekDaysCount,
            unsigned short lessonsCount,
            unsigned short classesCount,
            unsigned short subjectsCount,
            unsigned short teachersCount,
            unsigned short roomsCount,
            vector<unsigned short> classesSubjectsRestrictionStatus,
            vector<vector<unsigned short>> classesSubjects,
            vector<unsigned short> teachersSubjectsRestrictionStatus,
            vector<vector<unsigned short>> teachersSubjects,
            vector<unsigned short> roomsSubjectsRestrictionStatus,
            vector<vector<unsigned short>> roomsSubjects
    ) {
        int populationCount = 10;
        int generationNumber = 10;
        float crossoverProb = 0.2;
        float mutationProb = 0.1;

        // In order to have following commented code working, maybe refer to https://stackoverflow.com/questions/52211699/cython-cmake-and-setup-py-python-in-a-subdirectory-compiles-twice

        this->lessonplanGenAlgorithm = new LessonplanGenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb);

        auto* lessonplanData = new LessonplanData(
                weekDaysCount,
                lessonsCount,
                classesCount,
                subjectsCount,
                teachersCount,
                roomsCount,
                std::move(classesSubjectsRestrictionStatus),
                std::move(classesSubjects),
                std::move(teachersSubjectsRestrictionStatus),
                std::move(teachersSubjects),
                std::move(roomsSubjectsRestrictionStatus),
                std::move(roomsSubjects)
        );

        this->lessonplanGenAlgorithm->setAlgorithmData(lessonplanData);

        bool solutionFound = this->lessonplanGenAlgorithm->run();

        if (solutionFound) {
            return this->lessonplanGenAlgorithm->getLessonplanFromBestIndividual();
        }

    }

}
