#include <algorithm>
#include "../include/algorithm/LessonplanSchedulingAlgorithm.hpp"

namespace lessonplans {

    LessonplanSchedulingSolution* LessonplanSchedulingAlgorithm::findBestLessonplan(LessonplanSchedulingProblem* lessonplanSchedulingProblem) {
        this->findBestLessonplanWithGeneticAlgorithm(lessonplanSchedulingProblem);
    }

    LessonplanSchedulingSolution *LessonplanSchedulingAlgorithm::findBestLessonplanWithRandomSearch(
            LessonplanSchedulingProblem *lessonplanSchedulingProblem) {
        this->lessonplanSchedulingProblem = lessonplanSchedulingProblem;

        LessonplanIndividual* lessonplanIndividual = this->lessonplanSchedulingProblem->getSampleLessonplan();

        vector<vector<int>> obtainedScores = this->lessonplanSchedulingProblem->evaluateLessonplan(lessonplanIndividual);
        int summaryGrade = 0;
        std::for_each(obtainedScores[0].begin(), obtainedScores[0].end(), [&] (int grade) {
            summaryGrade += grade;
        });

        for (int i = 0; i < this->generationsCount; i++) {
            LessonplanIndividual* lessonplanIndividualAnother = this->lessonplanSchedulingProblem->getSampleLessonplan();

            vector<vector<int>> obtainedScoresAnother = this->lessonplanSchedulingProblem->evaluateLessonplan(lessonplanIndividual);
            int summaryGradeAnother = 0;
            std::for_each(obtainedScores[0].begin(), obtainedScores[0].end(), [&] (int grade) {
                summaryGradeAnother += grade;
            });

            if (obtainedScoresAnother > obtainedScores) {
                lessonplanIndividual = lessonplanIndividualAnother;
            }
        }

        auto* lessonplanSchedulingSoultion = new LessonplanSchedulingSolution(
                this->individualsCount,
                this->individuals,
                this->individualsScoresImportant,
                this->individualsSummaryScores
        );

        return lessonplanSchedulingSoultion;
    }

    LessonplanSchedulingSolution *LessonplanSchedulingAlgorithm::findBestLessonplanWithGreedyAlgorithm(
            LessonplanSchedulingProblem *lessonplanSchedulingProblem) {
        return nullptr;
    }

    LessonplanSchedulingSolution *LessonplanSchedulingAlgorithm::findBestLessonplanWithGeneticAlgorithm(
            LessonplanSchedulingProblem *lessonplanSchedulingProblem) {
        this->lessonplanSchedulingProblem = lessonplanSchedulingProblem;

        this->initializePopulation();
        this->evaluatePopulation();
        this->select();
        for (int i = 0; i < this->generationsCount; i++) {
            this->crossover();
            this->mutate();
            this->evaluatePopulation();
            this->select();
        }

        auto* lessonplanSchedulingSoultion = new LessonplanSchedulingSolution(
                this->individualsCount,
                this->individuals,
                this->individualsScoresImportant,
                this->individualsSummaryScores
        );

        return lessonplanSchedulingSoultion;
    }

    void LessonplanSchedulingAlgorithm::initializePopulation() {
        this->individuals = *new vector<LessonplanIndividual*>(
                this->individualsCount
        );
        this->individualsScoresImportant = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        LessonplanSchedulingProblem::scoresTypesImportant
                    )
        );
        this->individualsScoresOptimal = *new vector<vector<int>>(
                this->individualsCount, vector<int>(
                        LessonplanSchedulingProblem::scoresTypesOptimal
                )
        );
        this->individualsSummaryScores = *new vector<int>(
                this->individualsCount
        );

        for (int i = 0; i < this->individualsCount; i++) {
            this->individuals[i] = this->lessonplanSchedulingProblem->getSampleLessonplan();
        }
    }

    void LessonplanSchedulingAlgorithm::crossover() {

    }

    void LessonplanSchedulingAlgorithm::mutate() {

    }

    void LessonplanSchedulingAlgorithm::evaluatePopulation(){
        for (int i = 0; i < this->individualsCount; i++) {
            this->evaluateIndividual(i);
        }
    }

    void LessonplanSchedulingAlgorithm::evaluateIndividual(unsigned int individualIdx) {
        // Get scores for different aspects of problem
        vector<vector<int>> obtainedScores = this->lessonplanSchedulingProblem->evaluateLessonplan(this->individuals[individualIdx]);
        this->individualsScoresImportant[individualIdx] = obtainedScores[0];
        this->individualsScoresOptimal[individualIdx] = obtainedScores[1];

        // Sum all obtained scores together
        auto populationGradesCountImportant = static_cast<unsigned short>(this->individualsScoresImportant[individualIdx].size());
        this->individualsSummaryScores[individualIdx] = 0;
        for (unsigned short populationGradeIdx = 0; populationGradeIdx < populationGradesCountImportant; populationGradeIdx++) {
            this->individualsSummaryScores[individualIdx] += this->individualsScoresImportant[individualIdx][populationGradeIdx];
        }
        auto populationGradesCountOptimal = static_cast<unsigned short>(this->individualsScoresOptimal[individualIdx].size());
        this->individualsSummaryScores[individualIdx] = 0;
        for (unsigned short populationGradeIdx = 0; populationGradeIdx < populationGradesCountOptimal; populationGradeIdx++) {
            this->individualsSummaryScores[individualIdx] += this->individualsScoresOptimal[individualIdx][populationGradeIdx];
        }
    }

    void LessonplanSchedulingAlgorithm::select() {

    }

}
