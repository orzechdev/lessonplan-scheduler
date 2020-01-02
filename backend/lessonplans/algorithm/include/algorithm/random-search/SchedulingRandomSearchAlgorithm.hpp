#ifndef ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP
#define ALGORITHM_SCHEDULINGRANDOMSEARCHALGORITHM_HPP

#include "../SchedulingProblem.hpp"
#include "../SchedulingProblemProperties.hpp"
#include "../../lessonplan/LessonplanIndividual.hpp"
#include "../SchedulingSolution.hpp"
#include "../../lessonplan/LessonplanScoreList.hpp"

/*
 * Note: Some of the methods might be indicated by IDE as unused - it might not be true,
 * because IDE might not detect usages from Cython context.
 */
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
