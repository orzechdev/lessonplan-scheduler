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
                vector<vector<int>> individualsScores,
                vector<int> individualsSummaryScores
        ) :
                individualsCount(individualsCount),
                individuals(std::move(individuals)),
                individualsScores(std::move(individualsScores)),
                individualsSummaryScores(std::move(individualsSummaryScores)) {}

        vector<vector<unsigned short>> getBestLessonplan();

        vector<vector<vector<unsigned short>>> getAllLessonplans();

        vector<vector<int>> getAllLessonplansScores();

        vector<int> getAllLessonplansSummaryScores();

    private:
        int individualsCount;
        vector<LessonplanIndividual *> individuals;
        vector<vector<int>> individualsScores;
        vector<int> individualsSummaryScores;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGSOLUTION_HPP
