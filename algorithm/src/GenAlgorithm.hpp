#ifndef ALGORITHM_GENALGORITHM_HPP
#define ALGORITHM_GENALGORITHM_HPP

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
            virtual ~GenAlgorithm();
            virtual void setAlgorithmParams(
                    int populationCount,
                    int generationNumber,
                    float crossoverProb,
                    float mutationProb
            );
            virtual bool run();

        protected:
            int populationCount, generationNumber;
            float crossoverProb, mutationProb;
            virtual void initPopulation();
            virtual void crossover();
            virtual void mutate();
            virtual void evaluate();
            virtual void select();
        };
}

#endif //ALGORITHM_GENALGORITHM_HPP
