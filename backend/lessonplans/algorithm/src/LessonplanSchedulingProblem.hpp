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
        char evaluateLessonplan();
    private:
        LessonplanData* lessonplanData;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP
