#include <algorithm>
#include <chrono>
#include "../../../include/algorithm/genetic/SchedulingGeneticAlgorithm.hpp"
#include "../../../include/lessonplan/LessonplanScoreList.hpp"

namespace lessonplans {

    SchedulingGeneticAlgorithm::SchedulingGeneticAlgorithm(int calculationsTimeLimitInSeconds, int populationCount,
                                                           float crossoverProbability, float mutationProbability) {
        this->calculationsTimeLimitInSeconds = calculationsTimeLimitInSeconds;
        this->populationCount = populationCount;
        this->crossoverProbability = crossoverProbability;
        this->mutationProbability = mutationProbability;

        this->lessonplanScoreListPopulation = *new vector<LessonplanScoreList*>(
                this->populationCount
        );
    }

    SchedulingEvolutionalSolution *SchedulingGeneticAlgorithm::findBestLessonplan(SchedulingProblem *schedulingProblem) {
        auto start = std::chrono::steady_clock::now();
        auto end = start;
        auto timeToWait = std::chrono::seconds(calculationsTimeLimitInSeconds);

        vector<LessonplanIndividual *> currentPopulation = initializePopulation(schedulingProblem);
        evaluatePopulation(currentPopulation, schedulingProblem);

//        this->select();

        int generationIndex = 0;

        while (end - start < timeToWait && (lessonplanScoreListPopulation[generationIndex]->getScoreIndexWithZeroSummaryHardAndSoftScore() >= 0)) {
            crossoverPopulation();
            mutatePopulation();

            evaluatePopulation(currentPopulation, schedulingProblem);

            generationIndex++;

            end = std::chrono::steady_clock::now();
        }



//        for (int i = 0; i < this->calculationsTimeLimitInSeconds; i++) {
//            this->crossover();
//            this->mutate();
//            this->evaluatePopulation(schedulingProblem);
//            this->select();
//        }

        vector<SchedulingSolution *> schedulingSolutions;
        std::transform(
                lessonplanScoreListPopulation.begin(),
                lessonplanScoreListPopulation.end(),
                std::back_inserter(schedulingSolutions),
                [](LessonplanScoreList* lessonplanScoreList
        ) {
            return new SchedulingSolution(
                    nullptr,
                    lessonplanScoreList->getHardScores(),
                    lessonplanScoreList->getSoftScores(),
                    lessonplanScoreList->getSummaryHardScores(),
                    lessonplanScoreList->getSummarySoftScores(),
                    lessonplanScoreList->getLastScoreIndex()
            );
        });

        auto* lessonplanSchedulingEvolutionalSoultion = new SchedulingEvolutionalSolution(
                bestIndividual,
                schedulingSolutions,
                0
        );

        return lessonplanSchedulingEvolutionalSoultion;
    }

    vector<LessonplanIndividual *> SchedulingGeneticAlgorithm::initializePopulation(SchedulingProblem *schedulingProblem) {
        vector<LessonplanIndividual *> population = *new vector<LessonplanIndividual*>(
                this->populationCount
        );

        for (int i = 0; i < this->populationCount; i++) {
            population[i] = schedulingProblem->getSampleLessonplan();
        }

        return population;
    }

    void SchedulingGeneticAlgorithm::crossoverPopulation(){

    }

    void SchedulingGeneticAlgorithm::mutatePopulation(){

    }

    void SchedulingGeneticAlgorithm::evaluatePopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem){
        auto* lessonplanScoreList = new LessonplanScoreList();

        for (int i = 0; i < populationCount; i++) {
            vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(currentPopulation[i]);
            lessonplanScoreList->add(obtainedScores);
        }

        lessonplanScoreListPopulation.push_back(lessonplanScoreList);
    }

    void SchedulingGeneticAlgorithm::select() {

    }

}
