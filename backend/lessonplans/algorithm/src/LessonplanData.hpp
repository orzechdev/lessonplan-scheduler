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
            vector<vector<unsigned short>> classesSubjects,
            vector<vector<unsigned short>> teachersSubjects,
            vector<vector<unsigned short>> roomsSubjects
        );

        unsigned short getWeekDaysCount() const;

        unsigned short getLessonsCount() const;

        unsigned short getClassesCount() const;

        unsigned short getSubjectsCount() const;

        unsigned short getTeachersCount() const;

        unsigned short getRoomsCount() const;

        const vector<vector<unsigned short>> &getClassesSubjects() const;
        const vector<unsigned short> &getClassSubjects(unsigned short classIdx) const;

        const vector<vector<unsigned short>> &getTeachersSubjects() const;
        const vector<unsigned short> &getTeacherSubjects(unsigned short teacherIdx) const;

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
        vector<vector<unsigned short>> classesSubjects;
        vector<vector<unsigned short>> teachersSubjects;
        vector<vector<unsigned short>> roomsSubjects;
    };
}

#endif //ALGORITHM_LESSONPLANDATA_HPP
