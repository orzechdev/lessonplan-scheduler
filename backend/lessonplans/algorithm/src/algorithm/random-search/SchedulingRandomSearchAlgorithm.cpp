#include <algorithm>
#include <chrono>
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
        auto start = std::chrono::steady_clock::now();

        this->bestIndividual = schedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(this->bestIndividual);

        this->individualsHardScores[0] = obtainedScores[0];
        this->individualsSoftScores[0] = obtainedScores[1];

        this->individualsSummaryHardScores[0] = SchedulingProblem::calculateSummaryScore(obtainedScores[0]);
        this->individualsSummarySoftScores[0] = SchedulingProblem::calculateSummaryScore(obtainedScores[1]);

        int bestIndividualIdx = 0;
        int lastIdx = 0;

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

            lastIdx = i;
            auto end = std::chrono::steady_clock::now();

            if (end - start > std::chrono::minutes(1) || (this->individualsSummaryHardScores[i] == 0 && this->individualsSummarySoftScores[i] == 0)) {
                break;
            }
        }

        std::vector<std::vector<int>> subIndividualsHardScores(individualsHardScores.begin(), individualsHardScores.begin() + lastIdx);
        std::vector<std::vector<int>> subIndividualsSoftScores(individualsSoftScores.begin(), individualsSoftScores.begin() + lastIdx);
        std::vector<int> subIndividualsSummaryHardScores(individualsSummaryHardScores.begin(), individualsSummaryHardScores.begin() + lastIdx);
        std::vector<int> subIndividualsSummarySoftScores(individualsSummarySoftScores.begin(), individualsSummarySoftScores.begin() + lastIdx);

        auto *lessonplanSchedulingSoultion = new SchedulingSolution(
                this->bestIndividual,
                subIndividualsHardScores,
                subIndividualsSoftScores,
                subIndividualsSummaryHardScores,
                subIndividualsSummarySoftScores,
                bestIndividualIdx
        );

        return lessonplanSchedulingSoultion;
    }

}