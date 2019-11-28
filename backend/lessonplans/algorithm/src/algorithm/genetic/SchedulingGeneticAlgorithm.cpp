#include <algorithm>
#include "../../../include/algorithm/genetic/SchedulingGeneticAlgorithm.hpp"

namespace lessonplans {

    SchedulingSolution *SchedulingGeneticAlgorithm::findBestLessonplan(
            SchedulingProblem *schedulingProblem
    ) {
        this->schedulingProblem = schedulingProblem;

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
                this->individuals[0],
                this->individualsHardScores,
                this->individualsSoftScores,
                this->individualsSummaryHardScores,
                this->individualsSummarySoftScores,
                0
        );

        return lessonplanSchedulingSoultion;
    }

    void SchedulingGeneticAlgorithm::initializePopulation() {
        this->individuals = *new vector<LessonplanIndividual*>(
                this->individualsCount
        );

        this->individualsHardScores = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        SchedulingProblem::hardScoresTypes
                )
        );
        this->individualsSoftScores = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        SchedulingProblem::softScoresTypes
                )
        );
        this->individualsSummaryHardScores = *new vector<int>(
                this->individualsCount
        );
        this->individualsSummarySoftScores = *new vector<int>(
                this->individualsCount
        );

        for (int i = 0; i < this->individualsCount; i++) {
            this->individuals[i] = this->schedulingProblem->getSampleLessonplan();
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
        vector<vector<int>> obtainedScores = this->schedulingProblem->evaluateLessonplan(this->individuals[individualIdx]);
        this->individualsHardScores[individualIdx] = obtainedScores[0];
        this->individualsSoftScores[individualIdx] = obtainedScores[1];

        // Sum all obtained scores together
        auto populationHardScoresCount = static_cast<unsigned short>(this->individualsHardScores[individualIdx].size());
        this->individualsSummaryHardScores[individualIdx] = 0;
        for (unsigned short populationScoreIdx = 0; populationScoreIdx < populationHardScoresCount; populationScoreIdx++) {
            this->individualsSummaryHardScores[individualIdx] += this->individualsHardScores[individualIdx][populationScoreIdx];
        }
        auto populationSoftScoresCount = static_cast<unsigned short>(this->individualsSoftScores[individualIdx].size());
        this->individualsSummarySoftScores[individualIdx] = 0;
        for (unsigned short populationScoreIdx = 0; populationScoreIdx < populationSoftScoresCount; populationScoreIdx++) {
            this->individualsSummarySoftScores[individualIdx] += this->individualsSoftScores[individualIdx][populationScoreIdx];
        }
    }

    void SchedulingGeneticAlgorithm::select() {

    }

}
