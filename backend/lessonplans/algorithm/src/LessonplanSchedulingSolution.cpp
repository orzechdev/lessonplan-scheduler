#include <algorithm>
#include "../include/algorithm/LessonplanSchedulingSolution.hpp"

using std::max_element;
using std::distance;

namespace lessonplans {

    vector<vector<unsigned short>> LessonplanSchedulingSolution::getBestLessonplan() {
        int bestIndividualIndex = distance(this->individualsSummaryScores.begin(),
                                           max_element(this->individualsSummaryScores.begin(),
                                                       this->individualsSummaryScores.end()));
        return this->individuals[bestIndividualIndex]->getLessonplan();
    }

    vector<vector<vector<unsigned short>>> LessonplanSchedulingSolution::getAllLessonplans() {
        vector<vector<vector<unsigned short>>> lessonplans = *new vector<vector<vector<unsigned short>>>(
                this->individualsCount
        );

        std::transform(
                this->individuals.begin(),
                this->individuals.end(),
                lessonplans.begin(),
                [](LessonplanIndividual *lessonplanIndividual) {
                    return lessonplanIndividual->getLessonplan();
                }
        );

        return lessonplans;
    }

    vector<vector<int>> LessonplanSchedulingSolution::getAllLessonplansScores() {
        return this->individualsScores;
    }

    vector<int> LessonplanSchedulingSolution::getAllLessonplansSummaryScores() {
        return this->individualsSummaryScores;
    }
}