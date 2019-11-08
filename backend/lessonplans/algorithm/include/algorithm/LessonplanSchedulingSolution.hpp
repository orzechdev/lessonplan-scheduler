#ifndef ALGORITHM_LESSONPLANSCHEDULINGSOLUTION_HPP
#define ALGORITHM_LESSONPLANSCHEDULINGSOLUTION_HPP

#include <utility>
#include <vector>

#include "../../src/LessonplanIndividual.hpp"

using std::vector;

namespace lessonplans {
    class LessonplanSchedulingSolution {
    public:
        LessonplanSchedulingSolution(
                int individualsCount,
                vector<LessonplanIndividual *> individuals,
                vector<vector<int>> individualsHardScores,
                vector<vector<int>> individualsSoftScores,
                vector<int> individualsSummaryScores
        ) :
                individualsCount(individualsCount),
                individuals(std::move(individuals)),
                individualsHardScores(std::move(individualsHardScores)),
                individualsSoftScores(std::move(individualsSoftScores)),
                individualsSummaryScores(std::move(individualsSummaryScores)) {}

        vector<vector<unsigned short>> getBestLessonplan();

        vector<vector<vector<unsigned short>>> getAllLessonplans();

        vector<vector<int>> getAllLessonplansHardScores();

        vector<vector<int>> getAllLessonplansSoftScores();

        vector<int> getAllLessonplansSummaryScores();

    private:
        int individualsCount;
        vector<LessonplanIndividual *> individuals;
        vector<vector<int>> individualsHardScores;
        vector<vector<int>> individualsSoftScores;
        vector<int> individualsSummaryScores;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGSOLUTION_HPP
