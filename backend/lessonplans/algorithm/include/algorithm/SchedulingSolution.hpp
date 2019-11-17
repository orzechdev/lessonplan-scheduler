#ifndef ALGORITHM_SCHEDULINGSOLUTION_HPP
#define ALGORITHM_SCHEDULINGSOLUTION_HPP

#include <utility>
#include <vector>

#include "../../src/LessonplanIndividual.hpp"

using std::vector;

namespace lessonplans {
    class SchedulingSolution {
    public:
        SchedulingSolution(
                LessonplanIndividual* bestIndividual,
                vector<vector<int>> individualsHardScores,
                vector<vector<int>> individualsSoftScores,
                vector<int> individualsSummaryScores
        ) :
                bestIndividual(bestIndividual),
                individualsHardScores(std::move(individualsHardScores)),
                individualsSoftScores(std::move(individualsSoftScores)),
                individualsSummaryScores(std::move(individualsSummaryScores)) {}

        vector<vector<unsigned short>> getBestLessonplan();

        vector<vector<int>> getAllLessonplansHardScores();

        vector<vector<int>> getAllLessonplansSoftScores();

        vector<int> getAllLessonplansSummaryScores();

    private:
        LessonplanIndividual* bestIndividual;
        vector<vector<int>> individualsHardScores;
        vector<vector<int>> individualsSoftScores;
        vector<int> individualsSummaryScores;
    };
}

#endif //ALGORITHM_SCHEDULINGSOLUTION_HPP
