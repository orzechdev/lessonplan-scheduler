#include <algorithm>
#include "../../include/algorithm/SchedulingSolution.hpp"

using std::max_element;
using std::distance;

namespace lessonplans {

    vector<vector<unsigned short>> SchedulingSolution::getBestLessonplan() {
        return this->bestIndividual->getLessonplan();
    }

    vector<vector<int>> SchedulingSolution::getAllLessonplansHardScores() {
        return this->individualsHardScores;
    }

    vector<vector<int>> SchedulingSolution::getAllLessonplansSoftScores() {
        return this->individualsSoftScores;
    }

    vector<int> SchedulingSolution::getAllLessonplansSummaryHardScores() {
        return this->individualsSummaryHardScores;
    }

    vector<int> SchedulingSolution::getAllLessonplansSummarySoftScores() {
        return this->individualsSummarySoftScores;
    }

    int SchedulingSolution::getBestLessonplanScoreIndex() {
        return this->bestIndividualScoreIdx;
    }

}