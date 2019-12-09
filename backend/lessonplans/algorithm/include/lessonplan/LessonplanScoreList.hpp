#ifndef ALGORITHM_LESSONPLANGRADESLIST_HPP
#define ALGORITHM_LESSONPLANGRADESLIST_HPP

#include <vector>

using std::vector;

namespace lessonplans {
    class LessonplanScoreList {
    public:
        LessonplanScoreList();
        void add(vector<vector<int>> obtainedScores);
        vector<vector<int>> getHardScores();
        vector<vector<int>> getSoftScores();
        vector<int> getSummaryHardScores();
        vector<int> getSummarySoftScores();
        int getLastSummaryHardScore();
        int getLastSummarySoftScore();
        int getBestScoreIndex();
        int getLastScoreIndex();
        static const short hardScoresTypes = 4;
        static const short softScoresTypes = 3;

    private:
        int lastScoreIndex = -1;
        int bestScoreIndex = -1;
        vector<vector<int>> hardScores;
        vector<vector<int>> softScores;
        vector<int> summaryHardScores;
        vector<int> summarySoftScores;
        static int calculateSummaryScore(vector<int> obtainedScores);
    };
}

#endif //ALGORITHM_LESSONPLANGRADESLIST_HPP
