#ifndef ALGORITHM_SCHEDULINGPROBLEM_HPP
#define ALGORITHM_SCHEDULINGPROBLEM_HPP

#include "../../src/LessonplanIndividual.hpp"

namespace lessonplans {
    class SchedulingProblem {
    public:
        SchedulingProblem(SchedulingProblemProperties* schedulingProblemProperties) : schedulingProblemProperties(schedulingProblemProperties) {}
        LessonplanIndividual* getSampleLessonplan();
        vector<vector<int>> evaluateLessonplan(LessonplanIndividual* lessonplanIndividual);
        static const short hardScoresTypes = 4;
        static const short softScoresTypes = 3;
        static int calculateSummaryScore(vector<int> obtainedScores);
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
