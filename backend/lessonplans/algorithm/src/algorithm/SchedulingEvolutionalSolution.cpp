#include <algorithm>
#include "../../include/algorithm/SchedulingEvolutionalSolution.hpp"

using std::max_element;
using std::distance;

namespace lessonplans {

    vector<vector<unsigned short>> SchedulingEvolutionalSolution::getBestLessonplan() {
        return bestIndividual->getLessonplan();
    }

    vector<vector<vector<int>>> SchedulingEvolutionalSolution::getAllLessonplansHardScores() {
        int schedulingSolutionsCount = static_cast<int>(schedulingSolutions.size());

        vector<vector<vector<int>>> hardScores = *new vector<vector<vector<int>>>(
                schedulingSolutionsCount
        );

        for (int i = 0; i < schedulingSolutionsCount; i++) {
            hardScores[i] = schedulingSolutions[i]->getAllLessonplansHardScores();
        }

        return hardScores;
    }

    vector<vector<vector<int>>> SchedulingEvolutionalSolution::getAllLessonplansSoftScores() {
        int schedulingSolutionsCount = static_cast<int>(schedulingSolutions.size());

        vector<vector<vector<int>>> softScores = *new vector<vector<vector<int>>>(
                schedulingSolutionsCount
        );

        for (int i = 0; i < schedulingSolutionsCount; i++) {
            softScores[i] = schedulingSolutions[i]->getAllLessonplansSoftScores();
        }

        return softScores;
    }

    vector<vector<int>> SchedulingEvolutionalSolution::getAllLessonplansSummaryHardScores() {
        int schedulingSolutionsCount = static_cast<int>(schedulingSolutions.size());

        vector<vector<int>> summaryHardScores = *new vector<vector<int>>(
                schedulingSolutionsCount
        );

        for (int i = 0; i < schedulingSolutionsCount; i++) {
            summaryHardScores[i] = schedulingSolutions[i]->getAllLessonplansSummaryHardScores();
        }

        return summaryHardScores;
    }

    vector<vector<int>> SchedulingEvolutionalSolution::getAllLessonplansSummarySoftScores() {
        int schedulingSolutionsCount = static_cast<int>(schedulingSolutions.size());

        vector<vector<int>> summarySoftScores = *new vector<vector<int>>(
                schedulingSolutionsCount
        );

        for (int i = 0; i < schedulingSolutionsCount; i++) {
            summarySoftScores[i] = schedulingSolutions[i]->getAllLessonplansSummarySoftScores();
        }

        return summarySoftScores;
    }

    int SchedulingEvolutionalSolution::getBestLessonplanGenerationIndex() {
        return bestIndividualGenerationIdx;
    }

    int SchedulingEvolutionalSolution::getBestLessonplanGenerationScoreIndex() {
        return schedulingSolutions[bestIndividualGenerationIdx]->getBestLessonplanScoreIndex();
    }

}