#include <algorithm>
#include "../include/algorithm/SchedulingGreedyAlgorithm.hpp"

namespace lessonplans {

    SchedulingGreedyAlgorithm::SchedulingGreedyAlgorithm(int iterationsCount){
        this->iterationsCount = iterationsCount;

        this->individuals = *new vector<LessonplanIndividual*>(
                this->iterationsCount
        );
        this->individualsScoresImportant = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::scoresTypesImportant
                )
        );
        this->individualsScoresOptimal = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::scoresTypesOptimal
                )
        );
        this->individualsSummaryScores = *new vector<int>(
                this->iterationsCount
        );
    }

    SchedulingSolution *SchedulingGreedyAlgorithm::findBestLessonplan(SchedulingProblem *lessonplanSchedulingProblem) {
        this->individuals[0] = lessonplanSchedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = lessonplanSchedulingProblem->evaluateLessonplan(this->individuals[0]);

        this->individualsScoresImportant[0] = obtainedScores[0];
        this->individualsScoresOptimal[0] = obtainedScores[1];

        this->individualsSummaryScores[0] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores);

        int bestIndividualIdx = 0;

        for (int i = 1; i < this->iterationsCount; i++) {
            this->individuals[i] = this->alterLessonplan(this->individuals[bestIndividualIdx]);
            obtainedScores = lessonplanSchedulingProblem->evaluateLessonplan(this->individuals[i]);

            this->individualsScoresImportant[i] = obtainedScores[0];
            this->individualsScoresOptimal[i] = obtainedScores[1];

            this->individualsSummaryScores[i] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores);

            if (this->individualsSummaryScores[i] > this->individualsSummaryScores[bestIndividualIdx]) {
                bestIndividualIdx = i;
            }
        }

        auto* lessonplanSchedulingSoultion = new SchedulingSolution(
                this->iterationsCount,
                this->individuals,
                this->individualsScoresImportant,
                this->individualsScoresOptimal,
                this->individualsSummaryScores
        );

        return lessonplanSchedulingSoultion;
    }

    LessonplanIndividual *SchedulingGreedyAlgorithm::alterLessonplan(LessonplanIndividual *lessonplanIndividual) {
        /*
         * method not yet implemented
         */

        return nullptr;
    }

    int SchedulingGreedyAlgorithm::getSummaryScore(
            vector<vector<int>> obtainedScores
    ) {
        int summaryGrade = 0;
        std::for_each(obtainedScores[0].begin(), obtainedScores[0].end(), [&] (int grade) {
            summaryGrade += grade;
        });
        std::for_each(obtainedScores[1].begin(), obtainedScores[1].end(), [&] (int grade) {
            summaryGrade += grade;
        });
        return summaryGrade;
    }
}
