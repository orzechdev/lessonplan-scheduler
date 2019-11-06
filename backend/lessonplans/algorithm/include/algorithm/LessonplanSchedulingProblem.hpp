#ifndef ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP
#define ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP

#include "../../src/LessonplanIndividual.hpp"

namespace lessonplans {
    class LessonplanSchedulingProblem {
    public:
        LessonplanSchedulingProblem(LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties) : lessonplanSchedulingProblemProperties(lessonplanSchedulingProblemProperties) {}
        LessonplanIndividual* getSampleLessonplan();
        vector<vector<int>> evaluateLessonplan(LessonplanIndividual* lessonplanIndividual);
        static const short scoresTypesImportant = 3;
        static const short scoresTypesOptimal = 3;
    private:
        LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties;
        unsigned short checkTeachersWithSameTimesLessons(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkRoomWithSameTimesLessons(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkTeacherChangesForClassesSubjects(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkStartLessonsDifferenceBetweenDays(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkLessonsCountDifferenceBetweenDays(LessonplanIndividual* lessonplanIndividual);
        unsigned short checkFreePeriodsExistenceBetweenLessons(LessonplanIndividual* lessonplanIndividual);
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGPROBLEM_HPP
