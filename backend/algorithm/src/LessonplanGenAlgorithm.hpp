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
                    unsigned short dayCount,
                    unsigned short lessonCount,
                    // following data can be replaced by -> 255.255.255.255 -> 11111111.11111111.11111111.11111111
                    // so max no. of rooms is 255, subjects is 255, teachers is 255, classes is 255
                    // mutation would be created by replacing one of 255's with 255's in other's individuals in respective place
                    // following data can be replaced by -> 65535.65535.65535.65535 -> 1111111111111111.1111111111111111.1111111111111111.1111111111111111
                    // so max no. of rooms is 65535, subjects is 65535, teachers is 65535, classes is 65535
                    // mutation would be created by replacing one of 65535's with 65535's in other's individuals in respective place
                    std::vector<unsigned short> rooms,
                    std::vector<unsigned short> subjects,
                    std::vector<unsigned short> teachers,
                    std::vector<unsigned short> classes
            );
            std::vector<std::vector<std::vector<unsigned short>>> getLessonplanFromBestIndividual();

        private:
            unsigned short dayCount, lessonCount;
            std::vector<unsigned short> rooms, subjects, teachers, classes;
            // 255.255.255.255 -> 11111111.11111111.11111111.11111111 -> room.subject.teacher.class
            // 65535.65535.65535.65535 -> 1111111111111111.1111111111111111.1111111111111111.1111111111111111 -> room.subject.teacher.class
            std::vector<std::vector<std::vector<unsigned long long>>> population;
            void initPopulation() override;
            void crossover() override;
            void mutate() override;
            void evaluate() override;
            void select() override;
            static unsigned long long encodeIndividual(unsigned short room, unsigned short subject, unsigned short teacher, unsigned short classItem);
            static std::vector<unsigned short> decodeIndividual(unsigned long long individual);
            std::vector<std::vector<unsigned long long>> getBestIndividual();
    };
}

#endif //ALGORITHM_LESSONPLANGENALGORITHM_HPP
