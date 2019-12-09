#include <algorithm>
#include <chrono>
#include "../../../include/algorithm/random-search/SchedulingRandomSearchAlgorithm.hpp"

namespace lessonplans {

    SchedulingRandomSearchAlgorithm::SchedulingRandomSearchAlgorithm(int calculationsTimeLimitInSeconds) {
        this->calculationsTimeLimitInSeconds = calculationsTimeLimitInSeconds;

        this->lessonplanScoreList = new LessonplanScoreList();
    }

    SchedulingSolution *SchedulingRandomSearchAlgorithm::findBestLessonplan(
            SchedulingProblem *schedulingProblem
    ) {
        auto start = std::chrono::steady_clock::now();
        auto end = start;
        auto timeToWait = std::chrono::seconds(calculationsTimeLimitInSeconds);

        bestIndividual = schedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(bestIndividual);
        lessonplanScoreList->add(obtainedScores);

        while (end - start < timeToWait && (lessonplanScoreList->getLastSummaryHardScore() != 0 || lessonplanScoreList->getLastSummarySoftScore() != 0)) {
            LessonplanIndividual *currentIndividual = schedulingProblem->getSampleLessonplan();
            obtainedScores = schedulingProblem->evaluateLessonplan(currentIndividual);
            lessonplanScoreList->add(obtainedScores);

            if (lessonplanScoreList->getLastScoreIndex() == lessonplanScoreList->getBestScoreIndex()) {
                bestIndividual = currentIndividual;
            }

            end = std::chrono::steady_clock::now();
        }

        auto *lessonplanSchedulingSoultion = new SchedulingSolution(
                bestIndividual,
                lessonplanScoreList->getHardScores(),
                lessonplanScoreList->getSoftScores(),
                lessonplanScoreList->getSummaryHardScores(),
                lessonplanScoreList->getSummarySoftScores(),
                lessonplanScoreList->getBestScoreIndex()
        );

        return lessonplanSchedulingSoultion;
    }

}