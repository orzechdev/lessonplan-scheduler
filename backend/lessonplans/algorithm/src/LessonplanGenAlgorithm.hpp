#ifndef ALGORITHM_LESSONPLANGENALGORITHM_HPP
#define ALGORITHM_LESSONPLANGENALGORITHM_HPP

#include <vector>

#include "GenAlgorithm.hpp"
#include "LessonplanIndividual.hpp"
#include "LessonplanData.hpp"

using std::vector;

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
                    LessonplanData* lessonplanData
            );
            vector<vector<unsigned short>> getLessonplanFromBestIndividual();
            vector<vector<vector<unsigned short>>> getLessonplansFromAllIndividuals();

        private:
            /*
             * Input data
             */
            LessonplanData* lessonplanData;

            /*
             * Output data
             */
            vector<LessonplanIndividual*> population;

            /*
             * Methods
             */
            void initPopulation() override;
            void crossover() override;
            void mutate() override;
            void evaluate() override;
            void select() override;
            static unsigned long long encodeIndividualLesson(unsigned short room, unsigned short subject, unsigned short teacher, unsigned short classItem);
            static vector<unsigned short> decodeIndividualLesson(unsigned long long individualLesson);
            vector<unsigned short> getRandomTakingSequence(unsigned short sequenceSize);
    };
}

#endif //ALGORITHM_LESSONPLANGENALGORITHM_HPP
