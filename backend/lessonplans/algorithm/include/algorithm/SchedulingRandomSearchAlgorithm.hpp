#ifndef ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP
#define ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP

#include "SchedulingProblem.hpp"
#include "SchedulingProblemProperties.hpp"
#include "../../src/LessonplanIndividual.hpp"
#include "SchedulingSolution.hpp"

namespace lessonplans {
    class SchedulingRandomSearchAlgorithm {
    public:
        SchedulingRandomSearchAlgorithm(int iterationsCount);

        SchedulingSolution *findBestLessonplan(SchedulingProblem *schedulingProblem);

    private:
        int iterationsCount;
        vector<LessonplanIndividual *> individuals;
        vector<vector<int>> individualsScoresImportant;
        vector<vector<int>> individualsScoresOptimal;
        vector<int> individualsSummaryScores;

        static int getSummaryScore(vector<vector<int>> obtainedScores);
    };
}

#endif //ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP
