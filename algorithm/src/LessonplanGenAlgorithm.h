#ifndef ALGORITHM_LESSONPLANGENALGORITHM_H
#define ALGORITHM_LESSONPLANGENALGORITHM_H

#include <vector>

#include "GenAlgorithm.h"

namespace lessonplans {
    class LessonplanGenAlgorithm : public GenAlgorithm {
        public:
            LessonplanGenAlgorithm(
                    int populationCount,
                    int generationNumber,
                    float crossoverProb,
                    float mutationProb
            ) :
                    GenAlgorithm(populationCount, generationNumber, crossoverProb, mutationProb)
            {}
            void setAlgorithmData(
                    std::vector<int> lessons,
                    std::vector<int> rooms,
                    std::vector<int> subjects,
                    std::vector<int> teachers,
                    std::vector<int> classes
            );

        private:
            std::vector<int> lessons, rooms, subjects, teachers, classes;
            void initPopulation() override;
            void crossover() override;
            void mutate() override;
            void evaluate() override;
            void select() override;
    };
}

#endif //ALGORITHM_LESSONPLANGENALGORITHM_H
