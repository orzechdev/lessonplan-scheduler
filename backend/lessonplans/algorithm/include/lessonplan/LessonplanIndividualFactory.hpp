#ifndef ALGORITHM_LESSONPLANINDIVIDUALFACTORY_HPP
#define ALGORITHM_LESSONPLANINDIVIDUALFACTORY_HPP

#include "LessonplanIndividual.hpp"

namespace lessonplans {
    class LessonplanIndividualFactory {
    public:
        static LessonplanIndividual* createLessonplanIndividual(SchedulingProblemProperties* schedulingProblemProperties);
        static LessonplanIndividual* createLessonplanIndividualGreedly(SchedulingProblemProperties* schedulingProblemProperties);

    private:
        static unsigned int calculateMaxDataCount(SchedulingProblemProperties* lessonplanData);
        static void assignClassesWithSubjects(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanIndividualDescriptor* lessonplanIndividualDescriptor,
                SchedulingProblemProperties* schedulingProblemProperties
        );
        static bool tryAssignTeacher(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanIndividualDescriptor* lessonplanIndividualDescriptor,
                SchedulingProblemProperties* schedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId
        );
        static bool tryAssignRoom(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanIndividualDescriptor* lessonplanIndividualDescriptor,
                SchedulingProblemProperties* schedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId
        );
        static bool tryAssignWeekDayAndLesson(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanIndividualDescriptor* lessonplanIndividualDescriptor,
                SchedulingProblemProperties* schedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId
        );
        static void assignClassesWithSubjectsGreedly(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanIndividualDescriptor* lessonplanIndividualDescriptor,
                SchedulingProblemProperties* schedulingProblemProperties
        );
        static bool tryAssignTeacherGreedly(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanIndividualDescriptor* lessonplanIndividualDescriptor,
                SchedulingProblemProperties* schedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId,
                bool randomAssign
        );
        static bool tryAssignRoomGreedly(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanIndividualDescriptor* lessonplanIndividualDescriptor,
                SchedulingProblemProperties* schedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId,
                bool randomAssign
        );
        static bool tryAssignWeekDayAndLessonGreedly(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanIndividualDescriptor* lessonplanIndividualDescriptor,
                SchedulingProblemProperties* schedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId,
                bool randomAssign
        );
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUALFACTORY_HPP
