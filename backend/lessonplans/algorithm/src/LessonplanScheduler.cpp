#include "../include/algorithm/LessonplanScheduler.hpp"

#include <utility>

#include "LessonplanData.hpp"

namespace lessonplans {

    vector<vector<unsigned short>> LessonplanScheduler::scheduleLessonplan(
            unsigned short weekDaysCount,
            unsigned short lessonsCount,
            unsigned short classesCount,
            unsigned short subjectsCount,
            unsigned short teachersCount,
            unsigned short roomsCount,
            vector<vector<unsigned short>> classesSubjects,
            vector<vector<unsigned short>> teachersSubjects,
            vector<vector<unsigned short>> roomsSubjects
    ) {
        int populationCount = 100;
        int generationNumber = 10;
        float crossoverProb = 0.2;
        float mutationProb = 0.1;

        this->genAlgorithm = new GenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb);

        auto* lessonplanData = new LessonplanData(
                weekDaysCount,
                lessonsCount,
                classesCount,
                subjectsCount,
                teachersCount,
                roomsCount,
                std::move(classesSubjects),
                std::move(teachersSubjects),
                std::move(roomsSubjects)
        );

        auto* lessonplanSchedulingProblem = new LessonplanSchedulingProblem(lessonplanData);

        return this->genAlgorithm->findBestLessonplan(lessonplanSchedulingProblem);
    }

    vector<vector<unsigned short>> LessonplanScheduler::getBestLessonplan() {
        return this->genAlgorithm->getPreviouslyFoundBestLessonplan();
    }

    vector<vector<vector<unsigned short>>> LessonplanScheduler::getAllLessonplans() {
        return this->genAlgorithm->getPreviouslyFoundAllLessonplans();
    }

    vector<vector<int>> LessonplanScheduler::getAllLessonplansGrades() {
        return this->genAlgorithm->getPreviouslyFoundAllLessonplansGrades();
    }

    vector<int> LessonplanScheduler::getAllLessonplansGradesSums() {
        return this->genAlgorithm->getPreviouslyFoundAllLessonplansGradesSums();
    }

}
