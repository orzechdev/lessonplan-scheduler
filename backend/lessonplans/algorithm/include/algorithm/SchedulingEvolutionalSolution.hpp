#ifndef ALGORITHM_SCHEDULINGEVOLUTIONALSOLUTION_HPP
#define ALGORITHM_SCHEDULINGEVOLUTIONALSOLUTION_HPP

#include <utility>
#include <vector>

#include "../lessonplan/LessonplanIndividual.hpp"
#include "SchedulingSolution.hpp"

using std::vector;

namespace lessonplans {
    class SchedulingEvolutionalSolution {
    public:
        SchedulingEvolutionalSolution(
                LessonplanIndividual* bestIndividual,
                vector<SchedulingSolution *> schedulingSolutions,
                int bestIndividualGenerationIdx
        ) :
                bestIndividual(bestIndividual),
                schedulingSolutions(std::move(schedulingSolutions)),
                bestIndividualGenerationIdx(bestIndividualGenerationIdx) {}

        vector<vector<unsigned short>> getBestLessonplan();

        vector<vector<vector<int>>> getAllLessonplansHardScores();

        vector<vector<vector<int>>> getAllLessonplansSoftScores();

        vector<vector<int>> getAllLessonplansSummaryHardScores();

        vector<vector<int>> getAllLessonplansSummarySoftScores();

        int getBestLessonplanGenerationIndex();

        int getBestLessonplanGenerationScoreIndex();

    private:
        LessonplanIndividual* bestIndividual;
        vector<SchedulingSolution *> schedulingSolutions;
        int bestIndividualGenerationIdx;
    };
}

#endif //ALGORITHM_SCHEDULINGEVOLUTIONALSOLUTION_HPP
