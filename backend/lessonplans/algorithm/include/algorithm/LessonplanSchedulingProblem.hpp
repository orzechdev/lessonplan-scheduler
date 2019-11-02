#ifndef ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP
#define ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP

#include "../../src/LessonplanIndividual.hpp"

namespace lessonplans {
    class LessonplanSchedulingProblem {
    public:
        LessonplanSchedulingProblem(LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties) : lessonplanSchedulingProblemProperties(lessonplanSchedulingProblemProperties) {}
        LessonplanIndividual* getSampleLessonplan();
        vector<int> evaluateLessonplan(LessonplanIndividual* lessonplanIndividual);
        static const short scoresTypes = 3;
    private:
        LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties;
        unsigned short checkStartLessonsDifferenceBetweenDays(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkLessonsCountDifferenceBetweenDays(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkFreePeriodsExistenceBetweenLessons(LessonplanIndividual* lessonplanIndividual);
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP
