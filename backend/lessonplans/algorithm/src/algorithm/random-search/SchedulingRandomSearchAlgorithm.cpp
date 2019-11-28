#include <algorithm>
#include "../../../include/algorithm/random-search/SchedulingRandomSearchAlgorithm.hpp"

namespace lessonplans {

    SchedulingRandomSearchAlgorithm::SchedulingRandomSearchAlgorithm(int iterationsCount) {
        this->iterationsCount = iterationsCount;

        this->individualsHardScores = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::hardScoresTypes
                )
        );
        this->individualsSoftScores = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::softScoresTypes
                )
        );
        this->individualsSummaryHardScores = *new vector<int>(
                this->iterationsCount
        );
        this->individualsSummarySoftScores = *new vector<int>(
                this->iterationsCount
        );
    }

    SchedulingSolution *SchedulingRandomSearchAlgorithm::findBestLessonplan(
            SchedulingProblem *schedulingProblem
    ) {
        this->bestIndividual = schedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(this->bestIndividual);

        this->individualsHardScores[0] = obtainedScores[0];
        this->individualsSoftScores[0] = obtainedScores[1];

        this->individualsSummaryHardScores[0] = SchedulingProblem::calculateSummaryScore(obtainedScores[0]);
        this->individualsSummarySoftScores[0] = SchedulingProblem::calculateSummaryScore(obtainedScores[1]);

        int bestIndividualIdx = 0;

        for (int i = 1; i < this->iterationsCount; i++) {
            LessonplanIndividual *currentIndividual = schedulingProblem->getSampleLessonplan();
            obtainedScores = schedulingProblem->evaluateLessonplan(currentIndividual);

            this->individualsHardScores[i] = obtainedScores[0];
            this->individualsSoftScores[i] = obtainedScores[1];

            this->individualsSummaryHardScores[i] = SchedulingProblem::calculateSummaryScore(obtainedScores[0]);
            this->individualsSummarySoftScores[i] = SchedulingProblem::calculateSummaryScore(obtainedScores[1]);

            if (this->individualsSummaryHardScores[i] + this->individualsSummarySoftScores[i] >
                this->individualsSummaryHardScores[bestIndividualIdx] +
                this->individualsSummarySoftScores[bestIndividualIdx]) {
                bestIndividualIdx = i;
                this->bestIndividual = currentIndividual;
            }
        }

        auto *lessonplanSchedulingSoultion = new SchedulingSolution(
                this->bestIndividual,
                this->individualsHardScores,
                this->individualsSoftScores,
                this->individualsSummaryHardScores,
                this->individualsSummarySoftScores,
                bestIndividualIdx
        );

        return lessonplanSchedulingSoultion;
    }

}