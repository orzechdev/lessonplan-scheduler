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
        LessonplanSchedulingSolution *findBestLessonplanWithRandomSearch(LessonplanSchedulingProblem *lessonplanSchedulingProblem);
        LessonplanSchedulingSolution *findBestLessonplanWithGreedyAlgorithm(LessonplanSchedulingProblem *lessonplanSchedulingProblem);
        LessonplanSchedulingSolution *findBestLessonplanWithGeneticAlgorithm(LessonplanSchedulingProblem *lessonplanSchedulingProblem);

    private:
        int individualsCount, generationsCount;
        float crossoverProbability, mutationProbability;
        LessonplanSchedulingProblem *lessonplanSchedulingProblem;
        vector<LessonplanIndividual *> individuals;
        vector<vector<int>> individualsScoresImportant;
        vector<vector<int>> individualsScoresOptimal;
        vector<int> individualsSummaryScores;

        void initializePopulation();

        void crossover();

        void mutate();

        void evaluatePopulation();
        void evaluateIndividual(unsigned int individualIdx);

        void select();

        void mutateWeekDays();
        void mutateLessons();
        void mutateTeachers();
        void mutateRoom();
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGALGORITHM_HPP
