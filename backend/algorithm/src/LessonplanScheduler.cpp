#include "../include/algorithm/LessonplanScheduler.hpp"

#include "LessonplanGenAlgorithm.hpp"

namespace lessonplans {

    std::vector<std::vector<std::vector<std::vector<unsigned short>>>>
    LessonplanScheduler::scheduleLessonplan(unsigned short classCount, unsigned short dayCount,
                                            unsigned short lessonCount, std::vector<unsigned short> rooms,
                                            std::vector<unsigned short> teachers,
                                            std::vector<std::vector<std::vector<unsigned short>>> classesSubjectsIdsWithClassesSubjectsHours,
                                            std::vector<bool> roomsExclusiveAssignments,
                                            std::vector<std::vector<unsigned short>> subjectsRooms,
                                            std::vector<std::vector<unsigned short>> teachersSubjects) {
        int populationCount = 10;
        int generationNumber = 10;
        float crossoverProb = 0.2;
        float mutationProb = 0.1;

        // In order to have following commented code working, maybe refer to https://stackoverflow.com/questions/52211699/cython-cmake-and-setup-py-python-in-a-subdirectory-compiles-twice

        this->lessonplanGenAlgorithm = new LessonplanGenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb);

        this->lessonplanGenAlgorithm->setAlgorithmData(classCount, dayCount, lessonCount, rooms, teachers, classesSubjectsIdsWithClassesSubjectsHours);
        this->lessonplanGenAlgorithm->setAlgorithmConstraints(roomsExclusiveAssignments, subjectsRooms, teachersSubjects);

        bool solutionFound = this->lessonplanGenAlgorithm->run();

        if (solutionFound) {
            return this->lessonplanGenAlgorithm->getLessonplanFromBestIndividual();
        }

    }

}
