#include <algorithm>
#include <iostream>
#include "../../include/lessonplan/LessonplanScoreList.hpp"


namespace lessonplans {

    LessonplanScoreList::LessonplanScoreList() {
        hardScores = *new vector<vector<int>>(
                0, vector<int>(
                        LessonplanScoreList::hardScoresTypes
                )
        );
        softScores = *new vector<vector<int>>(
                0, vector<int>(
                        LessonplanScoreList::softScoresTypes
                )
        );
        summaryHardScores = *new vector<int>(
                0
        );
        summarySoftScores = *new vector<int>(
                0
        );
    }

    void LessonplanScoreList::add(vector<vector<int>> obtainedScores) {
        int newSummaryHardScore = LessonplanScoreList::calculateSummaryScore(obtainedScores[0]);
        int newSummarySoftScore = LessonplanScoreList::calculateSummaryScore(obtainedScores[1]);

        hardScores.push_back(obtainedScores[0]);
        softScores.push_back(obtainedScores[1]);
        summaryHardScores.push_back(newSummaryHardScore);
        summarySoftScores.push_back(newSummarySoftScore);

        if (lastScoreIndex >= 0) {
            lastScoreIndex++;

            int bestSummaryHardScore = summaryHardScores[bestScoreIndex];
            int bestSummarySoftScore = summarySoftScores[bestScoreIndex];

            bool hardScoreHigherThanBest = newSummaryHardScore > bestSummaryHardScore;
            bool hardScoreHigherOrEqualBest = newSummaryHardScore >= bestSummaryHardScore;
            bool softScoreHigherThanBest = newSummarySoftScore > bestSummarySoftScore;

            if (hardScoreHigherThanBest || (hardScoreHigherOrEqualBest && softScoreHigherThanBest)) {
                bestScoreIndex = lastScoreIndex;
            } else {
                int worstSummaryHardScore = summaryHardScores[worstScoreIndex];
                int worstSummarySoftScore = summarySoftScores[worstScoreIndex];

                bool hardScoreLowerThanWorst = newSummaryHardScore < worstSummaryHardScore;
                bool hardScoreLowerOrEqualWorst = newSummaryHardScore <= worstSummarySoftScore;
                bool softScoreHigherThanWorst = newSummarySoftScore < bestSummarySoftScore;

                if (hardScoreLowerThanWorst || (hardScoreLowerOrEqualWorst && softScoreHigherThanWorst)) {
                    worstScoreIndex = lastScoreIndex;
                }
            }
        } else {
            lastScoreIndex = 0;
            bestScoreIndex = lastScoreIndex;
            worstScoreIndex = lastScoreIndex;
        }

        if (newSummaryHardScore == 0 && newSummarySoftScore == 0) {
            scoreIndexWithZeroSummaryHardAndSoftScore = lastScoreIndex;
        }
    }

    vector<vector<int>> LessonplanScoreList::getHardScores() {
        return hardScores;
    }

    vector<vector<int>> LessonplanScoreList::getSoftScores() {
        return softScores;
    }

    vector<int> LessonplanScoreList::getSummaryHardScores() {
        return summaryHardScores;
    }

    vector<int> LessonplanScoreList::getSummarySoftScores() {
        return summarySoftScores;
    }

    int LessonplanScoreList::getBestScoreIndex() {
        return bestScoreIndex;
    }

    int LessonplanScoreList::getWorstScoreIndex() {
        return worstScoreIndex;
    }

    int LessonplanScoreList::getLastScoreIndex() {
        return lastScoreIndex;
    }

    int LessonplanScoreList::getScoreIndexWithZeroSummaryHardAndSoftScore() {
        return scoreIndexWithZeroSummaryHardAndSoftScore;
    }

    int LessonplanScoreList::calculateSummaryScore(
            vector<int> obtainedScores
    ) {
        int summaryScore = 0;
        std::for_each(obtainedScores.begin(), obtainedScores.end(), [&](int grade) {
            summaryScore += grade;
        });
        return summaryScore;
    }

    int LessonplanScoreList::getLastSummaryHardScore() {
        return summaryHardScores[lastScoreIndex];
    }

    int LessonplanScoreList::getLastSummarySoftScore() {
        return summarySoftScores[lastScoreIndex];
    }
}
