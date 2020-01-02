#ifndef ALGORITHM_SCHEDULINGPROBLEM_HPP
#define ALGORITHM_SCHEDULINGPROBLEM_HPP

#include "../lessonplan/LessonplanIndividual.hpp"

/*
 * Note: Some of the methods might be indicated by IDE as unused - it might not be true,
 * because IDE might not detect usages from Cython context.
 */
namespace lessonplans {
    class SchedulingProblem {
    public:
        SchedulingProblem(SchedulingProblemProperties* schedulingProblemProperties) : schedulingProblemProperties(schedulingProblemProperties) {}
        LessonplanIndividual* getSampleLessonplan();
        LessonplanIndividual* getSampleLessonplanGreedly();
        vector<vector<int>> evaluateLessonplan(LessonplanIndividual* lessonplanIndividual);
        SchedulingProblemProperties *getSchedulingProblemProperties() const;

    private:
        SchedulingProblemProperties* schedulingProblemProperties;
        unsigned short checkClassesSubjectsWithSameTimesLessons(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkTeachersWithSameTimesLessons(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkRoomWithSameTimesLessons(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkTeacherChangesForClassesSubjects(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkStartLessonsDifferenceBetweenDays(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkLessonsCountDifferenceBetweenDays(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkFreePeriodsExistenceBetweenLessons(LessonplanIndividual* lessonplanIndividual);
    };
}

#endif //ALGORITHM_SCHEDULINGPROBLEM_HPP
