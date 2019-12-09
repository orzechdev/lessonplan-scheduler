#ifndef ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP
#define ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP

#include "../SchedulingProblem.hpp"
#include "../SchedulingProblemProperties.hpp"
#include "../../lessonplan/LessonplanIndividual.hpp"
#include "../SchedulingSolution.hpp"
#include "../../lessonplan/LessonplanScoreList.hpp"

namespace lessonplans {
    class SchedulingRandomSearchAlgorithm {
    public:
        SchedulingRandomSearchAlgorithm(int calculationsTimeLimitInSeconds);

        SchedulingSolution *findBestLessonplan(SchedulingProblem *schedulingProblem);

    private:
        int calculationsTimeLimitInSeconds;
        LessonplanIndividual *bestIndividual;
        LessonplanScoreList *lessonplanScoreList;
    };
}

#endif //ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP
