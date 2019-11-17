#include <algorithm>
#include "../include/algorithm/SchedulingRandomSearchAlgorithm.hpp"

namespace lessonplans {

    SchedulingRandomSearchAlgorithm::SchedulingRandomSearchAlgorithm(int iterationsCount) {
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

    SchedulingSolution *SchedulingRandomSearchAlgorithm::findBestLessonplan(
            SchedulingProblem *schedulingProblem
    ) {
        this->individuals[0] = schedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(this->individuals[0]);

        this->individualsScoresImportant[0] = obtainedScores[0];
        this->individualsScoresOptimal[0] = obtainedScores[1];

        this->individualsSummaryScores[0] = SchedulingRandomSearchAlgorithm::getSummaryScore(obtainedScores);

        int bestIndividualIdx = 0;

        for (int i = 1; i < this->iterationsCount; i++) {
            this->individuals[i] = schedulingProblem->getSampleLessonplan();
            obtainedScores = schedulingProblem->evaluateLessonplan(this->individuals[i]);

            this->individualsScoresImportant[i] = obtainedScores[0];
            this->individualsScoresOptimal[i] = obtainedScores[1];

            this->individualsSummaryScores[i] = SchedulingRandomSearchAlgorithm::getSummaryScore(obtainedScores);

            if (this->individualsSummaryScores[i] > this->individualsSummaryScores[bestIndividualIdx]) {
                bestIndividualIdx = i;
            }
        }

        auto* lessonplanSchedulingSoultion = new SchedulingSolution(
                this->individuals[bestIndividualIdx],
                this->individualsScoresImportant,
                this->individualsScoresOptimal,
                this->individualsSummaryScores
        );

        return lessonplanSchedulingSoultion;
    }

    int SchedulingRandomSearchAlgorithm::getSummaryScore(
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