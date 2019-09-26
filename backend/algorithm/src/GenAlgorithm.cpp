#include "GenAlgorithm.hpp"

namespace lessonplans {

    GenAlgorithm::~GenAlgorithm(){
        //TODO: free memory
    }

    void GenAlgorithm::setAlgorithmParams(int populationCount, int generationNumber, float crossoverProb,
                                                    float mutationProb) {
        this->populationCount = populationCount;
        this->generationNumber = generationNumber;
        this->crossoverProb = crossoverProb;
        this->mutationProb = mutationProb;
    }

    bool GenAlgorithm::run() {
        //TODO: create generic run loop (execute for each iteration crossover, mutate, evaluate, select...)
        return true;
    }

}
