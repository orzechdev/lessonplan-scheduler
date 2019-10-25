#ifndef ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP
#define ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP

#include "LessonplanIndividual.hpp"

namespace lessonplans {
    class LessonplanSchedulingProblem {
    public:
        LessonplanSchedulingProblem(
                LessonplanData* lessonplanData
        ) :
                lessonplanData(lessonplanData)
        {}
        LessonplanIndividual* getSampleLessonplan();
        int evaluateLessonplan(LessonplanIndividual* lessonplanIndividual);
    private:
        LessonplanData* lessonplanData;
        unsigned short checkStartLessonsDifferenceBetweenDays(LessonplanIndividual* lessonplanIndividual, unsigned short maxValidStartLessonsDifferenceBetweenDays);
        unsigned short checkLessonsCountDifferenceBetweenDays(LessonplanIndividual* lessonplanIndividual, unsigned short maxValidLessonsCountDifferenceBetweenDays);
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP
