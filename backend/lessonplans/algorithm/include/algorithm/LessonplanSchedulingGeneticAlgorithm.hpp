#ifndef ALGORITHM_LESSONPLANSCHEDULINGGENETICALGORITHM_HPP
#define ALGORITHM_LESSONPLANSCHEDULINGGENETICALGORITHM_HPP

#include "LessonplanSchedulingProblem.hpp"
#include "LessonplanSchedulingProblemProperties.hpp"
#include "../../src/LessonplanIndividual.hpp"
#include "LessonplanSchedulingSolution.hpp"

namespace lessonplans {
    class LessonplanSchedulingGeneticAlgorithm {
    public:
        LessonplanSchedulingGeneticAlgorithm(
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

#endif //ALGORITHM_LESSONPLANSCHEDULINGGENETICALGORITHM_HPP
