#include <algorithm>
#include "../../include/algorithm/SchedulingSolution.hpp"

using std::max_element;
using std::distance;

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