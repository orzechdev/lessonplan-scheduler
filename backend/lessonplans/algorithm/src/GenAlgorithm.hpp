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
                    individualsCount(populationCount),
                    generationNumber(generationNumber),
                    crossoverProb(crossoverProb),
                    mutationProb(mutationProb)
            {}
            vector<vector<unsigned short>> findBestLessonplan(LessonplanSchedulingProblem* lessonplanSchedulingProblem);
            vector<vector<unsigned short>> getPreviouslyFoundBestLessonplan();
            vector<vector<vector<unsigned short>>> getPreviouslyFoundAllLessonplans();
            vector<vector<int>> getPreviouslyFoundAllLessonplansScores();
            vector<int> getPreviouslyFoundAllLessonplansSummaryScores();

        private:
            int individualsCount, generationNumber;
            float crossoverProb, mutationProb;
            LessonplanSchedulingProblem* lessonplanSchedulingProblem;
            vector<LessonplanIndividual*> individuals;
            vector<vector<int>> individualsScores;
            vector<int> individualsSummaryScores;
            void initializePopulation();
            void crossover();
            void mutate();
            void evaluate();
            void select();
        };
}

#endif //ALGORITHM_GENALGORITHM_HPP
