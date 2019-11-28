#ifndef ALGORITHM_SCHEDULINGGENETICALGORITHM_HPP
#define ALGORITHM_SCHEDULINGGENETICALGORITHM_HPP

#include "../SchedulingProblem.hpp"
#include "../SchedulingProblemProperties.hpp"
#include "../../lessonplan/LessonplanIndividual.hpp"
#include "../SchedulingSolution.hpp"

namespace lessonplans {
    class SchedulingGeneticAlgorithm {
    public:
        SchedulingGeneticAlgorithm(
                int populationCount,
                int generationsCount,
                float crossoverProbability,
                float mutationProbability
        ) :
                individualsCount(populationCount),
                generationsCount(generationsCount),
                crossoverProbability(crossoverProbability),
                mutationProbability(mutationProbability) {}

        SchedulingSolution *findBestLessonplan(SchedulingProblem *schedulingProblem);

    private:
        int individualsCount, generationsCount;
        float crossoverProbability, mutationProbability;
        SchedulingProblem *schedulingProblem;
        vector<LessonplanIndividual *> individuals;
//        vector<vector<int>> individualsScoresImportant;
//        vector<vector<int>> individualsScoresOptimal;
//        vector<int> individualsSummaryScores;
//        vector<int> individualsSummaryScores2;
        vector<vector<int>> individualsHardScores;
        vector<vector<int>> individualsSoftScores;
        vector<int> individualsSummaryHardScores;
        vector<int> individualsSummarySoftScores;

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

#endif //ALGORITHM_SCHEDULINGGENETICALGORITHM_HPP
