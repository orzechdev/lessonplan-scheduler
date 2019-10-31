#ifndef ALGORITHM_GENALGORITHM_HPP
#define ALGORITHM_GENALGORITHM_HPP

#include "LessonplanSchedulingProblem.hpp"
#include "LessonplanData.hpp"
#include "LessonplanIndividual.hpp"

namespace lessonplans {
    class GenAlgorithm {
        public:
            GenAlgorithm(
                    int populationCount,
                    int generationNumber,
                    float crossoverProb,
                    float mutationProb
            ) :
                    populationCount(populationCount),
                    generationNumber(generationNumber),
                    crossoverProb(crossoverProb),
                    mutationProb(mutationProb)
            {}
            ~GenAlgorithm();
            vector<vector<unsigned short>> findBestLessonplan(LessonplanSchedulingProblem* lessonplanSchedulingProblem);
            vector<vector<unsigned short>> getPreviouslyFoundBestLessonplan();
            vector<vector<vector<unsigned short>>> getPreviouslyFoundAllLessonplans();
            vector<vector<int>> getPreviouslyFoundAllLessonplansGrades();
            vector<int> getPreviouslyFoundAllLessonplansGradesSums();

        private:
            int populationCount, generationNumber;
            float crossoverProb, mutationProb;
            LessonplanSchedulingProblem* lessonplanSchedulingProblem;
            vector<LessonplanIndividual*> population;
            vector<int> populationGradesSums;
            vector<vector<int>> populationGrades;
            void initPopulation();
            void crossover();
            void mutate();
            void evaluate();
            void select();
        };
}

#endif //ALGORITHM_GENALGORITHM_HPP
