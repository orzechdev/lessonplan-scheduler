#ifndef ALGORITHM_LESSONPLANGENALGORITHM_HPP
#define ALGORITHM_LESSONPLANGENALGORITHM_HPP

#include <vector>

#include "GenAlgorithm.hpp"

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
                    unsigned short int dayCount,
                    unsigned short int lessonCount,
                    // following data can be replaced by -> 255.255.255.255 -> 11111111.11111111.11111111.11111111
                    // so max no. of rooms is 255, subjects is 255, teachers is 255, classes is 255
                    // mutation would be created by replacing one of 255's with 255's in other's individuals in respective place
                    std::vector<int> rooms,
                    std::vector<int> subjects,
                    std::vector<int> teachers,
                    std::vector<int> classes
            );
            std::vector<std::vector<int>> getLessonplan();

        private:
            unsigned short int dayCount, lessonCount;
            std::vector<int> rooms, subjects, teachers, classes;
            std::vector<std::vector<std::vector<int>>> population;
            void initPopulation() override;
            void crossover() override;
            void mutate() override;
            void evaluate() override;
            void select() override;
    };
}

#endif //ALGORITHM_LESSONPLANGENALGORITHM_HPP
