#ifndef ALGORITHM_SCHEDULINGGENETICALGORITHM_HPP
#define ALGORITHM_SCHEDULINGGENETICALGORITHM_HPP

#include "../SchedulingProblem.hpp"
#include "../SchedulingProblemProperties.hpp"
#include "../../lessonplan/LessonplanIndividual.hpp"
#include "../../lessonplan/LessonplanScoreList.hpp"
#include "../SchedulingEvolutionalSolution.hpp"

namespace lessonplans {
    class SchedulingGeneticAlgorithm {
    public:
        SchedulingGeneticAlgorithm(
                int calculationsTimeLimitInSeconds,
                int populationCount,
                float crossoverProbability,
                float mutationProbability
        );

        SchedulingEvolutionalSolution *findBestLessonplan(SchedulingProblem *schedulingProblem);

    private:
        int calculationsTimeLimitInSeconds, populationCount;
        float crossoverProbability, mutationProbability;
        LessonplanIndividual *bestIndividual;
        vector<LessonplanScoreList *> lessonplanScoreListPopulation;

        vector<LessonplanIndividual *> initializePopulation(SchedulingProblem *schedulingProblem);
        void evaluatePopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem);

        void mutatePopulation();
        void crossoverPopulation();

        void select();

        void mutateWeekDays();
        void mutateLessons();
        void mutateTeachers();
        void mutateRoom();
    };
}

#endif //ALGORITHM_SCHEDULINGGENETICALGORITHM_HPP
