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
        this->initPopulation(); // TODO: ...
        this->evaluate(); // TODO: ...
        this->select(); // TODO: ...
        for (int i = 0; i < this->generationNumber; i++) {
            this->crossover(); // TODO: ...
            this->mutate(); // TODO: ...
            this->evaluate(); // TODO: ...
            this->select(); // TODO: ...
        }
        return true;
    }

}
