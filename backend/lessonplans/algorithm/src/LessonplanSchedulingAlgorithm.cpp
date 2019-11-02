#include <algorithm>
#include "../include/algorithm/LessonplanSchedulingAlgorithm.hpp"

namespace lessonplans {

    LessonplanSchedulingSolution* LessonplanSchedulingAlgorithm::findBestLessonplan(LessonplanSchedulingProblem* lessonplanSchedulingProblem) {
        this->lessonplanSchedulingProblem = lessonplanSchedulingProblem;

        this->initializePopulation();
        this->evaluate(); // TODO: ...
        this->select(); // TODO: ...
        for (int i = 0; i < this->generationsCount; i++) {
            this->crossover(); // TODO: ...
            this->mutate(); // TODO: ...
            this->evaluate(); // TODO: ...
            this->select(); // TODO: ...
        }

        auto* lessonplanSchedulingSoultion = new LessonplanSchedulingSolution(
                this->individualsCount,
                this->individuals,
                this->individualsScores,
                this->individualsSummaryScores
                );

        return lessonplanSchedulingSoultion;
    }

    void LessonplanSchedulingAlgorithm::initializePopulation() {
        this->individuals = *new vector<LessonplanIndividual*>(
                this->individualsCount
        );
        this->individualsScores = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        LessonplanSchedulingProblem::scoresTypes
                    )
        );
        this->individualsSummaryScores = *new vector<int>(
                this->individualsCount
        );

        for (int i = 0; i < this->individualsCount; i++) {
            this->individuals[i] = this->lessonplanSchedulingProblem->getSampleLessonplan();
        }
    }

    void LessonplanSchedulingAlgorithm::crossover() {

    }

    void LessonplanSchedulingAlgorithm::mutate() {

    }

    void LessonplanSchedulingAlgorithm::evaluate() {
        for (int i = 0; i < this->individualsCount; i++) {
            this->individualsScores[i] = this->lessonplanSchedulingProblem->evaluateLessonplan(this->individuals[i]);

            auto populationGradesCount = static_cast<unsigned short>(this->individualsScores[i].size());
            this->individualsSummaryScores[i] = 0;
            for (unsigned short populationGradeIdx = 0; populationGradeIdx < populationGradesCount; populationGradeIdx++) {
                this->individualsSummaryScores[i] += this->individualsScores[i][populationGradeIdx];
            }
        }
    }

    void LessonplanSchedulingAlgorithm::select() {

    }

}
