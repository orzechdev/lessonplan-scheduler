#ifndef ALGORITHM_LESSONPLANSCHEDULINGALGORITHM_HPP
#define ALGORITHM_LESSONPLANSCHEDULINGALGORITHM_HPP

#include "LessonplanSchedulingProblem.hpp"
#include "LessonplanSchedulingProblemProperties.hpp"
#include "../../src/LessonplanIndividual.hpp"
#include "LessonplanSchedulingSolution.hpp"

namespace lessonplans {
    class LessonplanSchedulingAlgorithm {
    public:
        LessonplanSchedulingAlgorithm(
                int populationCount,
                int generationsCount,
                float crossoverProbability,
                float mutationProbability
        ) :
                individualsCount(populationCount),
                generationsCount(generationsCount),
                crossoverProbability(crossoverProbability),
                mutationProbability(mutationProbability) {}

        LessonplanSchedulingSolution *findBestLessonplan(LessonplanSchedulingProblem *lessonplanSchedulingProblem);

    private:
        int individualsCount, generationsCount;
        float crossoverProbability, mutationProbability;
        LessonplanSchedulingProblem *lessonplanSchedulingProblem;
        vector<LessonplanIndividual *> individuals;
        vector<vector<int>> individualsScores;
        vector<int> individualsSummaryScores;

        void initializePopulation();

        void crossover();

        void mutate();

        void evaluate();

        void select();
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGALGORITHM_HPP
