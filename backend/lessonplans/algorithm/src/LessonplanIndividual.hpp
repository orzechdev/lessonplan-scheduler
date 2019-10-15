#ifndef ALGORITHM_LESSONPLANINDIVIDUAL_HPP
#define ALGORITHM_LESSONPLANINDIVIDUAL_HPP

#include <vector>

#include "Individual.hpp"
#include "LessonplanData.hpp"

using std::vector;

namespace lessonplans {
    class LessonplanIndividual : public Individual {
    public:
        LessonplanIndividual() : Individual() {}
        vector<vector<unsigned short>> initLessonplan(LessonplanData* lessonplanData);
        vector<vector<unsigned short>> getIndividual();

    private:
        static const short dataTypes = 6;
        unsigned int maxDataCount;
        vector<vector<unsigned short>> individual;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms;
        bool tryAssignTeacher(
                LessonplanData* lessonplanData,
                unsigned short individualDataIdx,
                unsigned short classIdx,
                unsigned short classId, unsigned short subjectId
        );
        bool tryAssignRoom(
                LessonplanData* lessonplanData,
                unsigned short individualDataIdx,
                unsigned short classIdx, unsigned short teacherIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId
        );
        bool tryAssignWeekDayAndLesson(
                LessonplanData* lessonplanData,
                unsigned short individualDataIdx,
                unsigned short classIdx, unsigned short teacherIdx, unsigned short roomIdx,
                unsigned short classId, unsigned short subjectId, unsigned short teacherId, unsigned short roomId
        );
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUAL_HPP
