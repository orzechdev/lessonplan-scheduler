#ifndef ALGORITHM_LESSONPLANINDIVIDUAL_HPP
#define ALGORITHM_LESSONPLANINDIVIDUAL_HPP

#include <vector>

#include "../include/algorithm/LessonplanSchedulingProblemProperties.hpp"

using std::vector;

namespace lessonplans {
    class LessonplanIndividual {
    public:
        LessonplanIndividual(LessonplanSchedulingProblemProperties* lessonplanSchedulingProblemProperties);
        vector<vector<unsigned short>> getLessonplan();
        unsigned int getMaxDataCount() const;
        static const short dataTypes = 6;

    private:
        unsigned int maxDataCount;
        vector<vector<unsigned short>> lessonplan;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms;
        bool tryAssignTeacher(
                LessonplanSchedulingProblemProperties* lessonplanData,
                unsigned short individualDataIdx,
                unsigned short classIdx,
                unsigned short classId, unsigned short subjectId
        );
        bool tryAssignRoom(
                LessonplanSchedulingProblemProperties* lessonplanData,
                unsigned short individualDataIdx,
                unsigned short classIdx, unsigned short teacherIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId
        );
        bool tryAssignWeekDayAndLesson(
                LessonplanSchedulingProblemProperties* lessonplanData,
                unsigned short individualDataIdx,
                unsigned short classIdx, unsigned short teacherIdx, unsigned short roomIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId
        );
        static unsigned int calculateMaxDataCount(LessonplanSchedulingProblemProperties* lessonplanData);
        static vector<unsigned short> getRandomIdxsSequence(unsigned short sequenceSize);
        static vector<unsigned short> getRandomIdsSequence(unsigned short sequenceSize);
        static vector<unsigned short> getRandomNumbersSequence(unsigned short sequenceSize, unsigned short lowestNumber);
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUAL_HPP
