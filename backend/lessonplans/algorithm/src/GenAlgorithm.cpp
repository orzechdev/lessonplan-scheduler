#include <algorithm>
#include "GenAlgorithm.hpp"

namespace lessonplans {

    vector<vector<unsigned short>> GenAlgorithm::findBestLessonplan(LessonplanSchedulingProblem* lessonplanSchedulingProblem) {
        this->lessonplanSchedulingProblem = lessonplanSchedulingProblem;

        this->initializePopulation();
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

    void GenAlgorithm::initializePopulation() {
        this->individuals = *new vector<LessonplanIndividual*>(
                this->individualsCount
        );
        this->individualsScores = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        LessonplanSchedulingProblem::scoresTypes
                    )
        );
        this->individualsSummaryScores = *new vector<int>(
                this->individualsCount
        );

        for (int i = 0; i < this->individualsCount; i++) {
            this->individuals[i] = this->lessonplanSchedulingProblem->getSampleLessonplan();
        }
    }

    void GenAlgorithm::crossover() {

    }

    void GenAlgorithm::mutate() {

    }

    void GenAlgorithm::evaluate() {
        for (int i = 0; i < this->individualsCount; i++) {
            this->individualsScores[i] = this->lessonplanSchedulingProblem->evaluateLessonplan(this->individuals[i]);

            auto populationGradesCount = static_cast<unsigned short>(this->individualsScores[i].size());
            this->individualsSummaryScores[i] = 0;
            for (unsigned short populationGradeIdx = 0; populationGradeIdx < populationGradesCount; populationGradeIdx++) {
                this->individualsSummaryScores[i] += this->individualsScores[i][populationGradeIdx];
            }
        }
    }

    void GenAlgorithm::select() {

    }

    vector<vector<unsigned short>> GenAlgorithm::getPreviouslyFoundBestLessonplan() {
        int bestIndividualIndex = std::distance(this->individualsSummaryScores.begin(), std::max_element(this->individualsSummaryScores.begin(), this->individualsSummaryScores.end()));
        return this->individuals[bestIndividualIndex]->getLessonplan();
    }

    vector<vector<vector<unsigned short>>> GenAlgorithm::getPreviouslyFoundAllLessonplans() {
        vector<vector<vector<unsigned short>>> lessonplans = *new vector<vector<vector<unsigned short>>>(
                this->individualsCount
        );

        std::transform(
                this->individuals.begin(),
                this->individuals.end(),
                lessonplans.begin(),
                [](LessonplanIndividual* lessonplanIndividual) {
                    return lessonplanIndividual->getLessonplan();
                }
        );

        return lessonplans;
    }

    vector<vector<int>> GenAlgorithm::getPreviouslyFoundAllLessonplansScores() {
        return this->individualsScores;
    }

    vector<int> GenAlgorithm::getPreviouslyFoundAllLessonplansSummaryScores() {
        return this->individualsSummaryScores;
    }

}
