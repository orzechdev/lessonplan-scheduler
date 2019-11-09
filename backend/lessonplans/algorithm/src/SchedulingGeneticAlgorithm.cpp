#include <algorithm>
#include "../include/algorithm/SchedulingGeneticAlgorithm.hpp"

namespace lessonplans {

    SchedulingSolution *SchedulingGeneticAlgorithm::findBestLessonplan(
            SchedulingProblem *lessonplanSchedulingProblem
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

        auto* lessonplanSchedulingSoultion = new SchedulingSolution(
                this->individualsCount,
                this->individuals,
                this->individualsScoresImportant,
                this->individualsScoresOptimal,
                this->individualsSummaryScores
        );

        return lessonplanSchedulingSoultion;
    }

    void SchedulingGeneticAlgorithm::initializePopulation() {
        this->individuals = *new vector<LessonplanIndividual*>(
                this->individualsCount
        );
        this->individualsScoresImportant = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        SchedulingProblem::scoresTypesImportant
                    )
        );
        this->individualsScoresOptimal = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        SchedulingProblem::scoresTypesOptimal
                )
        );
        this->individualsSummaryScores = *new vector<int>(
                this->individualsCount
        );

        for (int i = 0; i < this->individualsCount; i++) {
            this->individuals[i] = this->lessonplanSchedulingProblem->getSampleLessonplan();
        }
    }

    void SchedulingGeneticAlgorithm::crossover() {

    }

    void SchedulingGeneticAlgorithm::mutate() {

    }

    void SchedulingGeneticAlgorithm::evaluatePopulation(){
        for (int i = 0; i < this->individualsCount; i++) {
            this->evaluateIndividual(i);
        }
    }

    void SchedulingGeneticAlgorithm::evaluateIndividual(unsigned int individualIdx) {
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

    void SchedulingGeneticAlgorithm::select() {

    }

}
