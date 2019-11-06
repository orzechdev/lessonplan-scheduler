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
        this->individualsSummaryScores[0] = this->getSummaryScore(this->individuals[0], lessonplanSchedulingProblem);

        int bestIndividualIdx = 0;

        for (int i = 1; i < this->iterationsCount; i++) {
            this->individuals[i] = lessonplanSchedulingProblem->getSampleLessonplan();
            this->individualsSummaryScores[i] = this->getSummaryScore(this->individuals[i], lessonplanSchedulingProblem);

            if (this->individualsSummaryScores[i] > this->individualsSummaryScores[bestIndividualIdx]) {
                bestIndividualIdx = i;
            }
        }

        auto* lessonplanSchedulingSoultion = new LessonplanSchedulingSolution(
                this->iterationsCount,
                this->individuals,
                this->individualsScoresImportant,
                this->individualsSummaryScores
        );

        return lessonplanSchedulingSoultion;
    }

    int LessonplanSchedulingRandomSearchAlgorithm::getSummaryScore(
            LessonplanIndividual* lessonplanIndividual, LessonplanSchedulingProblem *lessonplanSchedulingProblem
    ) {
        vector<vector<int>> obtainedScores = lessonplanSchedulingProblem->evaluateLessonplan(lessonplanIndividual);
        int summaryGrade = 0;
        std::for_each(obtainedScores[0].begin(), obtainedScores[0].end(), [&] (int grade) {
            summaryGrade += grade;
        });
        return summaryGrade;
    }
}