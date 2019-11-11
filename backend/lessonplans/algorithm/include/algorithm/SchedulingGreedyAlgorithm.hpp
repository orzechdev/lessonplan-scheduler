#ifndef ALGORITHM_SCHEDULINGGREEDYALGORITHM_HPP
#define ALGORITHM_SCHEDULINGGREEDYALGORITHM_HPP

#include "SchedulingProblem.hpp"
#include "SchedulingProblemProperties.hpp"
#include "../../src/LessonplanIndividual.hpp"
#include "SchedulingSolution.hpp"

namespace lessonplans {
    class SchedulingGreedyAlgorithm {
    public:
        SchedulingGreedyAlgorithm(int iterationsCount);

        SchedulingSolution *findBestLessonplan(SchedulingProblem *schedulingProblem);

    private:
        int iterationsCount;
        vector<LessonplanIndividual *> individuals;
        vector<vector<int>> individualsScoresImportant;
        vector<vector<int>> individualsScoresOptimal;
        vector<int> individualsSummaryScores;

        LessonplanIndividual* alterLessonplan(LessonplanIndividual* lessonplanIndividual, SchedulingProblem *schedulingProblem);

        static int getSummaryScore(vector<vector<int>> obtainedScores);
    };
}

#endif //ALGORITHM_SCHEDULINGGREEDYALGORITHM_HPP
