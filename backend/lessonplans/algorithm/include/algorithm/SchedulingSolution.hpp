#ifndef ALGORITHM_SCHEDULINGSOLUTION_HPP
#define ALGORITHM_SCHEDULINGSOLUTION_HPP

#include <utility>
#include <vector>

#include "../lessonplan/LessonplanIndividual.hpp"

using std::vector;

/*
 * Note: Some of the methods might be indicated by IDE as unused - it might not be true,
 * because IDE might not detect usages from Cython context.
 */
namespace lessonplans {
    class SchedulingSolution {
    public:
        SchedulingSolution(
                LessonplanIndividual* bestIndividual,
                vector<vector<int>> individualsHardScores,
                vector<vector<int>> individualsSoftScores,
                vector<int> individualsSummaryHardScores,
                vector<int> individualsSummarySoftScores,
                int bestIndividualScoreIdx
        ) :
                bestIndividual(bestIndividual),
                individualsHardScores(std::move(individualsHardScores)),
                individualsSoftScores(std::move(individualsSoftScores)),
                individualsSummaryHardScores(std::move(individualsSummaryHardScores)),
                individualsSummarySoftScores(std::move(individualsSummarySoftScores)),
                bestIndividualScoreIdx(bestIndividualScoreIdx) {}

        vector<vector<unsigned short>> getBestLessonplan();

        vector<vector<int>> getAllLessonplansHardScores();

        vector<vector<int>> getAllLessonplansSoftScores();

        vector<int> getAllLessonplansSummaryHardScores();

        vector<int> getAllLessonplansSummarySoftScores();

        int getBestLessonplanScoreIndex();

    private:
        LessonplanIndividual* bestIndividual;
        vector<vector<int>> individualsHardScores;
        vector<vector<int>> individualsSoftScores;
        vector<int> individualsSummaryHardScores;
        vector<int> individualsSummarySoftScores;
        int bestIndividualScoreIdx;
    };
}

#endif //ALGORITHM_SCHEDULINGSOLUTION_HPP
