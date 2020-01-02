#include <algorithm>
#include "../../include/algorithm/SchedulingSolution.hpp"

using std::max_element;
using std::distance;

/*
 * Note: Some of the methods might be indicated by IDE as unused - it might not be true,
 * because IDE might not detect usages from Cython context.
 */
namespace lessonplans {

    vector<vector<unsigned short>> SchedulingSolution::getBestLessonplan() {
        return bestIndividual->getLessonplan();
    }

    vector<vector<int>> SchedulingSolution::getAllLessonplansHardScores() {
        return individualsHardScores;
    }

    vector<vector<int>> SchedulingSolution::getAllLessonplansSoftScores() {
        return individualsSoftScores;
    }

    vector<int> SchedulingSolution::getAllLessonplansSummaryHardScores() {
        return individualsSummaryHardScores;
    }

    vector<int> SchedulingSolution::getAllLessonplansSummarySoftScores() {
        return individualsSummarySoftScores;
    }

    int SchedulingSolution::getBestLessonplanScoreIndex() {
        return bestIndividualScoreIdx;
    }

}