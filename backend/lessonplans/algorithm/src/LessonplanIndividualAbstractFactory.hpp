#ifndef ALGORITHM_LESSONPLANINDIVIDUALABSTRACTFACTORY_HPP
#define ALGORITHM_LESSONPLANINDIVIDUALABSTRACTFACTORY_HPP

#include "LessonplanIndividual.hpp"

namespace lessonplans {
    class LessonplanIndividualAbstractFactory {
    public:
        static LessonplanIndividual* createLessonplanIndividual(SchedulingProblemProperties* schedulingProblemProperties);

    private:
        static unsigned int calculateMaxDataCount(SchedulingProblemProperties* lessonplanData);
        static void assignClassesWithSubjects(
                LessonplanIndividual* lessonplanIndividual,
                SchedulingProblemProperties* schedulingProblemProperties
        );
        static bool tryAssignTeacher(
                LessonplanIndividual* lessonplanIndividual,
                SchedulingProblemProperties* schedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId
        );
        static bool tryAssignRoom(
                LessonplanIndividual* lessonplanIndividual,
                SchedulingProblemProperties* schedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId
        );
        static bool tryAssignWeekDayAndLesson(
                LessonplanIndividual* lessonplanIndividual,
                SchedulingProblemProperties* schedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId
        );
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUALABSTRACTFACTORY_HPP
