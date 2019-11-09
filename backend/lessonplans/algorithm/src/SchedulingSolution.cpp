#include <algorithm>
#include "../include/algorithm/SchedulingSolution.hpp"

using std::max_element;
using std::distance;

namespace lessonplans {

    vector<vector<unsigned short>> SchedulingSolution::getBestLessonplan() {
        int bestIndividualIndex = distance(this->individualsSummaryScores.begin(),
                                           max_element(this->individualsSummaryScores.begin(),
                                                       this->individualsSummaryScores.end()));
        return this->individuals[bestIndividualIndex]->getLessonplan();
    }

    vector<vector<vector<unsigned short>>> SchedulingSolution::getAllLessonplans() {
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

    vector<vector<int>> SchedulingSolution::getAllLessonplansHardScores() {
        return this->individualsHardScores;
    }

    vector<vector<int>> SchedulingSolution::getAllLessonplansSoftScores() {
        return this->individualsSoftScores;
    }

    vector<int> SchedulingSolution::getAllLessonplansSummaryScores() {
        return this->individualsSummaryScores;
    }

}