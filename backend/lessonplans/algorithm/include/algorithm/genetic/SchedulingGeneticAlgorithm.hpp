#ifndef ALGORITHM_SCHEDULINGGENETICALGORITHM_HPP
#define ALGORITHM_SCHEDULINGGENETICALGORITHM_HPP

#include "../SchedulingProblem.hpp"
#include "../SchedulingProblemProperties.hpp"
#include "../../lessonplan/LessonplanIndividual.hpp"
#include "../../lessonplan/LessonplanScoreList.hpp"
#include "../SchedulingEvolutionalSolution.hpp"

/*
 * Note: Some of the methods might be indicated by IDE as unused - it might not be true,
 * because IDE might not detect usages from Cython context.
 */
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
        void evaluatePopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem, bool addScoreForNewGeneration);

        vector<LessonplanIndividual *> crossoverPopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem, int generationIndex);
        void mutatePopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem, int generationIndex);

        int select(int generationIndex, int populationHardScoreSum, int populationSoftScoreSum, bool includeSoftScore, int excludeIndex);

        LessonplanIndividual *
        reformLessonplan(LessonplanIndividual *lessonplanIndividual, SchedulingProblem *schedulingProblem, int generationIndex);

        void reformLessonplanTeacherDataItem(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                             SchedulingProblemProperties *schedulingProblemProperties,
                                             vector<unsigned short> *lessonplanDataItem);

        void
        reformLessonplanRoomDataItem(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                     SchedulingProblemProperties *schedulingProblemProperties,
                                     vector<unsigned short> *lessonplanDataItem);

        void reformLessonplanClassSubjectDataItem(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                                  SchedulingProblemProperties *schedulingProblemProperties,
                                                  vector<unsigned short> *lessonplanDataItem);

        void reformLessonplanClassSubjectTeacher(LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
                                                 SchedulingProblemProperties *schedulingProblemProperties,
                                                 vector<unsigned short> *lessonplanDataItem,
                                                 vector<vector<unsigned short>> *classesSubjectsTeachersToAssign);

        static unsigned short
        findTeacherForClassSubject(SchedulingProblemProperties *schedulingProblemProperties, unsigned short subjectId);
    };
}

#endif //ALGORITHM_SCHEDULINGGENETICALGORITHM_HPP
