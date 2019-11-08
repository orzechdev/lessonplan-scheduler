#include <algorithm>
#include "../include/algorithm/LessonplanSchedulingGeneticAlgorithm.hpp"

namespace lessonplans {

    LessonplanSchedulingSolution *LessonplanSchedulingGeneticAlgorithm::findBestLessonplan(
            LessonplanSchedulingProblem *lessonplanSchedulingProblem
    ) {
        this->lessonplanSchedulingProblem = lessonplanSchedulingProblem;

        this->initializePopulation();
        this->evaluatePopulation();
        this->select();
        for (int i = 0; i < this->generationsCount; i++) {
            this->crossover();
            this->mutate();
            this->evaluatePopulation();
            this->select();
        }

        auto* lessonplanSchedulingSoultion = new LessonplanSchedulingSolution(
                this->individualsCount,
                this->individuals,
                this->individualsScoresImportant,
                this->individualsScoresOptimal,
                this->individualsSummaryScores
        );

        return lessonplanSchedulingSoultion;
    }

    void LessonplanSchedulingGeneticAlgorithm::initializePopulation() {
        this->individuals = *new vector<LessonplanIndividual*>(
                this->individualsCount
        );
        this->individualsScoresImportant = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        LessonplanSchedulingProblem::scoresTypesImportant
                    )
        );
        this->individualsScoresOptimal = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        LessonplanSchedulingProblem::scoresTypesOptimal
                )
        );
        this->individualsSummaryScores = *new vector<int>(
                this->individualsCount
        );

        for (int i = 0; i < this->individualsCount; i++) {
            this->individuals[i] = this->lessonplanSchedulingProblem->getSampleLessonplan();
        }
    }

    void LessonplanSchedulingGeneticAlgorithm::crossover() {

    }

    void LessonplanSchedulingGeneticAlgorithm::mutate() {

    }

    void LessonplanSchedulingGeneticAlgorithm::evaluatePopulation(){
        for (int i = 0; i < this->individualsCount; i++) {
            this->evaluateIndividual(i);
        }
    }

    void LessonplanSchedulingGeneticAlgorithm::evaluateIndividual(unsigned int individualIdx) {
        // Get scores for different aspects of problem
        vector<vector<int>> obtainedScores = this->lessonplanSchedulingProblem->evaluateLessonplan(this->individuals[individualIdx]);
        this->individualsScoresImportant[individualIdx] = obtainedScores[0];
        this->individualsScoresOptimal[individualIdx] = obtainedScores[1];

        // Sum all obtained scores together
        auto populationGradesCountImportant = static_cast<unsigned short>(this->individualsScoresImportant[individualIdx].size());
        this->individualsSummaryScores[individualIdx] = 0;
        for (unsigned short populationGradeIdx = 0; populationGradeIdx < populationGradesCountImportant; populationGradeIdx++) {
            this->individualsSummaryScores[individualIdx] += this->individualsScoresImportant[individualIdx][populationGradeIdx];
        }
        auto populationGradesCountOptimal = static_cast<unsigned short>(this->individualsScoresOptimal[individualIdx].size());
        this->individualsSummaryScores[individualIdx] = 0;
        for (unsigned short populationGradeIdx = 0; populationGradeIdx < populationGradesCountOptimal; populationGradeIdx++) {
            this->individualsSummaryScores[individualIdx] += this->individualsScoresOptimal[individualIdx][populationGradeIdx];
        }
    }

    void LessonplanSchedulingGeneticAlgorithm::select() {

    }

}
