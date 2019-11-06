#ifndef ALGORITHM_LESSONPLANSCHEDULINGRANDOMSEARCHALGORITHM_HPP
#define ALGORITHM_LESSONPLANSCHEDULINGRANDOMSEARCHALGORITHM_HPP

#include "LessonplanSchedulingProblem.hpp"
#include "LessonplanSchedulingProblemProperties.hpp"
#include "../../src/LessonplanIndividual.hpp"
#include "LessonplanSchedulingSolution.hpp"

namespace lessonplans {
    class LessonplanSchedulingRandomSearchAlgorithm {
    public:
        LessonplanSchedulingRandomSearchAlgorithm(int iterationsCount);

        LessonplanSchedulingSolution *findBestLessonplan(LessonplanSchedulingProblem *lessonplanSchedulingProblem);

    private:
        int iterationsCount;
        vector<LessonplanIndividual *> individuals;
        vector<vector<int>> individualsScoresImportant;
        vector<vector<int>> individualsScoresOptimal;
        vector<int> individualsSummaryScores;

        int getSummaryScore(LessonplanIndividual *lessonplanIndividual, LessonplanSchedulingProblem *lessonplanSchedulingProblem);
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGRANDOMSEARCHALGORITHM_HPP
