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

        return this->getPreviouslyFoundBestLessonplan();
    }

    void GenAlgorithm::initPopulation() {
        this->population = *new vector<LessonplanIndividual*>(
                this->populationCount
        );
        this->populationGrades = *new vector<vector<int>>(
                this->populationCount, vector<int>(
                        LessonplanSchedulingProblem::gradesTypes
                    )
        );
        this->populationGradesSums = *new vector<int>(
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
        for (int i = 0; i < this->populationCount; i++) {
            this->populationGrades[i] = this->lessonplanSchedulingProblem->evaluateLessonplan(this->population[i]);

            auto populationGradesCount = static_cast<unsigned short>(this->populationGrades[i].size());
            this->populationGradesSums[i] = 0;
            for (unsigned short populationGradeIdx = 0; populationGradeIdx < populationGradesCount; populationGradeIdx++) {
                this->populationGradesSums[i] += this->populationGrades[i][populationGradeIdx];
            }
        }
    }

    void GenAlgorithm::select() {

    }

    vector<vector<unsigned short>> GenAlgorithm::getPreviouslyFoundBestLessonplan() {
        int bestIndividualIndex = std::distance(this->populationGradesSums.begin(), std::max_element(this->populationGradesSums.begin(), this->populationGradesSums.end()));
        return this->population[bestIndividualIndex]->getIndividual();
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

    vector<vector<int>> GenAlgorithm::getPreviouslyFoundAllLessonplansGrades() {
        return this->populationGrades;
    }

    vector<int> GenAlgorithm::getPreviouslyFoundAllLessonplansGradesSums() {
        return this->populationGradesSums;
    }

}
