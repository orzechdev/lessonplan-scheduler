#ifndef ALGORITHM_LESSONPLANINDIVIDUALABSTRACTFACTORY_HPP
#define ALGORITHM_LESSONPLANINDIVIDUALABSTRACTFACTORY_HPP

#include "LessonplanIndividual.hpp"

namespace lessonplans {
    class LessonplanIndividualAbstractFactory {
    public:
        static LessonplanIndividual* createLessonplanIndividual(LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties);

    private:
        static unsigned int calculateMaxDataCount(LessonplanSchedulingProblemProperties* lessonplanData);
        static void assignClassesWithSubjects(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties
        );
        static bool tryAssignTeacher(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId
        );
        static bool tryAssignRoom(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId
        );
        static bool tryAssignWeekDayAndLesson(
                LessonplanIndividual* lessonplanIndividual,
                LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties,
                unsigned short individualDataIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId
        );
        static vector<unsigned short> getRandomIdxsSequence(unsigned short sequenceSize);
        static vector<unsigned short> getRandomIdsSequence(unsigned short sequenceSize);
        static vector<unsigned short> getRandomNumbersSequence(unsigned short sequenceSize, unsigned short lowestNumber);
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUALABSTRACTFACTORY_HPP
