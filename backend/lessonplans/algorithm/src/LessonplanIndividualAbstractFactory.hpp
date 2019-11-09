#ifndef ALGORITHM_LESSONPLANINDIVIDUALABSTRACTFACTORY_HPP
#define ALGORITHM_LESSONPLANINDIVIDUALABSTRACTFACTORY_HPP

#include "LessonplanIndividual.hpp"

namespace lessonplans {
    class LessonplanIndividualAbstractFactory {
    public:
        static LessonplanIndividual* createLessonplanIndividual(SchedulingProblemProperties* lessonplanSchedulingProblemProperties);

    private:
        static unsigned int calculateMaxDataCount(SchedulingProblemProperties* lessonplanData);
        static void assignClassesWithSubjects(
                LessonplanIndividual* lessonplanIndividual,
                SchedulingProblemProperties* lessonplanSchedulingProblemProperties
        );
        static bool tryAssignTeacher(
                LessonplanIndividual* lessonplanIndividual,
                SchedulingProblemProperties* lessonplanSchedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId
        );
        static bool tryAssignRoom(
                LessonplanIndividual* lessonplanIndividual,
                SchedulingProblemProperties* lessonplanSchedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId
        );
        static bool tryAssignWeekDayAndLesson(
                LessonplanIndividual* lessonplanIndividual,
                SchedulingProblemProperties* lessonplanSchedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId
        );
        static vector<unsigned short> getRandomIdxsSequence(unsigned short sequenceSize);
        static vector<unsigned short> getRandomIdsSequence(unsigned short sequenceSize);
        static vector<unsigned short> getRandomNumbersSequence(unsigned short sequenceSize, unsigned short lowestNumber);
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUALABSTRACTFACTORY_HPP
