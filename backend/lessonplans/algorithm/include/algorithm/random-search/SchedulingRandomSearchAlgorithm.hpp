#ifndef ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP
#define ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP

#include "../SchedulingProblem.hpp"
#include "../SchedulingProblemProperties.hpp"
#include "../../lessonplan/LessonplanIndividual.hpp"
#include "../SchedulingSolution.hpp"

namespace lessonplans {
    class SchedulingRandomSearchAlgorithm {
    public:
        SchedulingRandomSearchAlgorithm(int iterationsCount);

        SchedulingSolution *findBestLessonplan(SchedulingProblem *schedulingProblem);

    private:
        int iterationsCount;
        LessonplanIndividual *bestIndividual;
        vector<vector<int>> individualsHardScores;
        vector<vector<int>> individualsSoftScores;
        vector<int> individualsSummaryHardScores;
        vector<int> individualsSummarySoftScores;
    };
}

#endif //ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP
