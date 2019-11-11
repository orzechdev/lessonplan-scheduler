#ifndef ALGORITHM_LESSONPLANINDIVIDUAL_HPP
#define ALGORITHM_LESSONPLANINDIVIDUAL_HPP

#include <vector>

#include "../include/algorithm/SchedulingProblemProperties.hpp"

using std::vector;

namespace lessonplans {
    class LessonplanIndividual {
    public:
        unsigned int getMaxDataCount() const;

        void setMaxDataCount(unsigned int maxDataCount);

        vector<vector<unsigned short>> getLessonplan();

        void setLessonplan(vector<vector<unsigned short>> lessonplan);

        void setLessonplanDataItem(unsigned short dataIdx, unsigned short weekDayId, unsigned short lessonId,
                                   unsigned short classId, unsigned short subjectId, unsigned short teacherId,
                                   unsigned short roomId);

        void setLessonplanDataItemWeekDay(unsigned short dataIdx, unsigned short weekDayId);

        void setLessonplanDataItemLesson(unsigned short dataIdx, unsigned short lessonId);

        void setLessonplanDataItemTeacher(unsigned short dataIdx, unsigned short teacherId);

        void setLessonplanDataItemRoom(unsigned short dataIdx, unsigned short roomId);

        unsigned short getAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                      unsigned short classIdx) const;

        void setAssignedLessonAndDaysToClasses(vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses);

        void setAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                            unsigned short classIdx);

        unsigned short
        getAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                         unsigned short teacherIdx) const;

        void setAssignedLessonAndDaysToTeachers(vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers);

        void setAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                              unsigned short teacherIdx);

        unsigned short getAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                     unsigned short roomIdx) const;

        void setAssignedLessonAndDaysToRooms(vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms);

        void setAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                           unsigned short roomIdx);

        static const short dataTypes = 6;

    private:
        unsigned int maxDataCount;
        vector<vector<unsigned short>> lessonplan;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms;
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUAL_HPP
