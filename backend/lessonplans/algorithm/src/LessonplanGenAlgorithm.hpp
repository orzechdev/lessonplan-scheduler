#ifndef ALGORITHM_LESSONPLANGENALGORITHM_HPP
#define ALGORITHM_LESSONPLANGENALGORITHM_HPP

#include <vector>

#include "GenAlgorithm.hpp"
#include "LessonplanIndividual.hpp"

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
                    unsigned short weekDaysCount,
                    unsigned short lessonsCount,
                    unsigned short classesCount,
                    unsigned short subjectsCount,
                    unsigned short teachersCount,
                    unsigned short roomsCount,
                    std::vector<unsigned short> classesSubjectsRestrictionStatus,
                    std::vector<std::vector<unsigned short>> classesSubjects,
                    std::vector<unsigned short> teachersSubjectsRestrictionStatus,
                    std::vector<std::vector<unsigned short>> teachersSubjects,
                    std::vector<unsigned short> roomsSubjectsRestrictionStatus,
                    std::vector<std::vector<unsigned short>> roomsSubjects
            );
            std::vector<std::vector<unsigned short>> getLessonplanFromBestIndividual();

        private:
            /*
             * Input data
             */
            unsigned short weekDaysCount;
            unsigned short lessonsCount;
            unsigned short classesCount;
            unsigned short subjectsCount;
            unsigned short teachersCount;
            unsigned short roomsCount;
            // Population constraints
            std::vector<unsigned short> classesSubjectsRestrictionStatus;
            std::vector<std::vector<unsigned short>> classesSubjects;
            std::vector<unsigned short> teachersSubjectsRestrictionStatus;
            std::vector<std::vector<unsigned short>> teachersSubjects;
            std::vector<unsigned short> roomsSubjectsRestrictionStatus;
            std::vector<std::vector<unsigned short>> roomsSubjects;

            /*
             * Output data
             */
            std::vector<LessonplanIndividual> population;

            /*
             * Methods
             */
            void initPopulation() override;
            void crossover() override;
            void mutate() override;
            void evaluate() override;
            void select() override;
            static unsigned long long encodeIndividualLesson(unsigned short room, unsigned short subject, unsigned short teacher, unsigned short classItem);
            static std::vector<unsigned short> decodeIndividualLesson(unsigned long long individualLesson);
            std::vector<unsigned short> getRandomTakingSequence(unsigned short sequenceSize);
            std::vector<std::vector<unsigned short>> getBestIndividual();
    };
}

#endif //ALGORITHM_LESSONPLANGENALGORITHM_HPP
