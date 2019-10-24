#include <algorithm>
#include "GenAlgorithm.hpp"

namespace lessonplans {

    GenAlgorithm::~GenAlgorithm(){
        //TODO: free memory
    }

    vector<vector<unsigned short>> GenAlgorithm::findBestLessonplan(LessonplanSchedulingProblem* lessonplanSchedulingProblem) {
        this->lessonplanSchedulingProblem = lessonplanSchedulingProblem;

        this->initPopulation(); // TODO: ...
        this->evaluate(); // TODO: ...
        this->select(); // TODO: ...
        for (int i = 0; i < this->generationNumber; i++) {
            this->crossover(); // TODO: ...
            this->mutate(); // TODO: ...
            this->evaluate(); // TODO: ...
            this->select(); // TODO: ...
        }

        return this->population[0]->getIndividual();
    }

    void GenAlgorithm::initPopulation() {
        this->population = *new vector<LessonplanIndividual*>(
                this->populationCount
        );

        for (int i = 0; i < this->populationCount; i++) {
            this->population[i] = this->lessonplanSchedulingProblem->getSampleLessonplan();
        }
    }

    void GenAlgorithm::crossover() {

    }

    void GenAlgorithm::mutate() {

    }

    void GenAlgorithm::evaluate() {

    }

    void GenAlgorithm::select() {

    }

    vector<vector<unsigned short>> GenAlgorithm::getPreviouslyFoundBestLessonplan() {
        return this->population[0]->getIndividual();
    }

    vector<vector<vector<unsigned short>>> GenAlgorithm::getPreviouslyFoundAllLessonplans() {
        vector<vector<vector<unsigned short>>> lessonplans = *new vector<vector<vector<unsigned short>>>(
                this->populationCount
        );

        std::transform(
                this->population.begin(),
                this->population.end(),
                lessonplans.begin(),
                [](LessonplanIndividual* lessonplanIndividual) {
                    return lessonplanIndividual->getIndividual();
                }
        );

        return lessonplans;
    }

}
