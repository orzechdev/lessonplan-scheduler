#ifndef ALGORITHM_LESSONPLANDATA_HPP
#define ALGORITHM_LESSONPLANDATA_HPP

#include <vector>

using std::vector;

namespace lessonplans {
    class LessonplanData {
    public:
        LessonplanData(
            unsigned short weekDaysCount, unsigned short lessonsCount, unsigned short classesCount,
            unsigned short subjectsCount, unsigned short teachersCount, unsigned short roomsCount,
            vector<unsigned short> classesSubjectsRestrictionStatus,
            vector<vector<unsigned short>> classesSubjects,
            vector<unsigned short> teachersSubjectsRestrictionStatus,
            vector<vector<unsigned short>> teachersSubjects,
            vector<unsigned short> roomsSubjectsRestrictionStatus,
            vector<vector<unsigned short>> roomsSubjects
        );

        unsigned short getWeekDaysCount() const;

        unsigned short getLessonsCount() const;

        unsigned short getClassesCount() const;

        unsigned short getSubjectsCount() const;

        unsigned short getTeachersCount() const;

        unsigned short getRoomsCount() const;

        const vector<unsigned short> &getClassesSubjectsRestrictionStatus() const;
        const unsigned short &getClassSubjectsRestrictionStatus(unsigned short classIdx) const;

        const vector<vector<unsigned short>> &getClassesSubjects() const;
        const vector<unsigned short> &getClassSubjects(unsigned short classIdx) const;

        const vector<unsigned short> &getTeachersSubjectsRestrictionStatus() const;
        const unsigned short &getTeacherSubjectsRestrictionStatus(unsigned short teacherIdx) const;

        const vector<vector<unsigned short>> &getTeachersSubjects() const;
        const vector<unsigned short> &getTeacherSubjects(unsigned short teacherIdx) const;

        const vector<unsigned short> &getRoomsSubjectsRestrictionStatus() const;
        const unsigned short &getRoomSubjectsRestrictionStatus(unsigned short roomIdx) const;

        const vector<vector<unsigned short>> &getRoomsSubjects() const;
        const vector<unsigned short> &getRoomSubjects(unsigned short roomIdx) const;

    private:
        unsigned short weekDaysCount;
        unsigned short lessonsCount;
        unsigned short classesCount;
        unsigned short subjectsCount;
        unsigned short teachersCount;
        unsigned short roomsCount;
        // Population constraints
        vector<unsigned short> classesSubjectsRestrictionStatus;
        vector<vector<unsigned short>> classesSubjects;
        vector<unsigned short> teachersSubjectsRestrictionStatus;
        vector<vector<unsigned short>> teachersSubjects;
        vector<unsigned short> roomsSubjectsRestrictionStatus;
        vector<vector<unsigned short>> roomsSubjects;
    };
}

#endif //ALGORITHM_LESSONPLANDATA_HPP
