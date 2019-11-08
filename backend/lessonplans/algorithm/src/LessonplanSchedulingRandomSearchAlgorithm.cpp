#include <algorithm>
#include "../include/algorithm/LessonplanSchedulingRandomSearchAlgorithm.hpp"

namespace lessonplans {

    LessonplanSchedulingRandomSearchAlgorithm::LessonplanSchedulingRandomSearchAlgorithm(int iterationsCount) {
        this->iterationsCount = iterationsCount;

        this->individuals = *new vector<LessonplanIndividual*>(
                this->iterationsCount
        );
        this->individualsScoresImportant = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        LessonplanSchedulingProblem::scoresTypesImportant
                )
        );
        this->individualsScoresOptimal = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        LessonplanSchedulingProblem::scoresTypesOptimal
                )
        );
        this->individualsSummaryScores = *new vector<int>(
                this->iterationsCount
        );
    }

    LessonplanSchedulingSolution *LessonplanSchedulingRandomSearchAlgorithm::findBestLessonplan(
            LessonplanSchedulingProblem *lessonplanSchedulingProblem
    ) {
        this->individuals[0] = lessonplanSchedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = lessonplanSchedulingProblem->evaluateLessonplan(this->individuals[0]);

        this->individualsScoresImportant[0] = obtainedScores[0];
        this->individualsScoresOptimal[0] = obtainedScores[1];

        this->individualsSummaryScores[0] = LessonplanSchedulingRandomSearchAlgorithm::getSummaryScore(obtainedScores);

        int bestIndividualIdx = 0;

        for (int i = 1; i < this->iterationsCount; i++) {
            this->individuals[i] = lessonplanSchedulingProblem->getSampleLessonplan();
            obtainedScores = lessonplanSchedulingProblem->evaluateLessonplan(this->individuals[i]);

            this->individualsScoresImportant[i] = obtainedScores[0];
            this->individualsScoresOptimal[i] = obtainedScores[1];

            this->individualsSummaryScores[i] = LessonplanSchedulingRandomSearchAlgorithm::getSummaryScore(obtainedScores);

            if (this->individualsSummaryScores[i] > this->individualsSummaryScores[bestIndividualIdx]) {
                bestIndividualIdx = i;
            }
        }

        auto* lessonplanSchedulingSoultion = new LessonplanSchedulingSolution(
                this->iterationsCount,
                this->individuals,
                this->individualsScoresImportant,
                this->individualsScoresOptimal,
                this->individualsSummaryScores
        );

        return lessonplanSchedulingSoultion;
    }

    int LessonplanSchedulingRandomSearchAlgorithm::getSummaryScore(
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