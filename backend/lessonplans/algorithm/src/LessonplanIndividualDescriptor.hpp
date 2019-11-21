#ifndef ALGORITHM_LESSONPLANINDIVIDUALDESCRIPTOR_HPP
#define ALGORITHM_LESSONPLANINDIVIDUALDESCRIPTOR_HPP

#include <vector>

using std::vector;

namespace lessonplans {
    class LessonplanIndividualDescriptor {
    public:
        vector<vector<vector<unsigned short>>> getAssignedLessonAndDaysToClasses() const;

        vector<vector<vector<unsigned short>>> getAssignedLessonAndDaysToTeachers() const;

        vector<vector<vector<unsigned short>>> getAssignedLessonAndDaysToRooms() const;

        void setAssignedLessonAndDaysToClasses(vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses);

        void setAssignedLessonAndDaysToTeachers(vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers);

        void setAssignedLessonAndDaysToRooms(vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms);

        unsigned short getAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                      unsigned short classIdx) const;

        unsigned short
        getAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                         unsigned short teacherIdx) const;

        unsigned short getAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                     unsigned short roomIdx) const;

        void increaseAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                 unsigned short classIdx);

        void increaseAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                   unsigned short teacherIdx);

        void increaseAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                unsigned short roomIdx);

        void decreaseAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                 unsigned short classIdx);


        void decreaseAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                   unsigned short teacherIdx);


        void decreaseAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx, unsigned short currentLessonIdx,
                                                unsigned short roomIdx);

        vector<unsigned short> getClassesStartLessonsDifferenceCountAverage() const;

        void setClassesStartLessonsDifferenceCountAverage(vector<unsigned short> classesStartLessonsDifferenceCountAverage);

        vector<unsigned short> getClassesLessonsCountAverageDifferenceBetweenDays() const;

        void setClassesLessonsCountAverageDifferenceBetweenDays(vector<unsigned short> classesLessonsCountAverageDifferenceBetweenDays);

        vector<unsigned short> getClassesFreePeriodsExistenceBetweenLessonsCount() const;

        void setClassesFreePeriodsExistenceBetweenLessonsCount(vector<unsigned short> classesFreePeriodsExistenceBetweenLessonsCount);

    private:
        int invalidClassesSubjectsSameLessonsTimesCount;
        int invalidTeachersSameLessonsTimesCount;
        int invalidRoomsSameLessonTimesCount;
        int invalidTeachersChangesForClassesSubjectsCount;

        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers;
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms;

        vector<unsigned short> classesStartLessonsDifferenceCountAverage;
        vector<unsigned short> classesLessonsCountAverageDifferenceBetweenDays;
        vector<unsigned short> classesFreePeriodsExistenceBetweenLessonsCount;
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUALDESCRIPTOR_HPP
