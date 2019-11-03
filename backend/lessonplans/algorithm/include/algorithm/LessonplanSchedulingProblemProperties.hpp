#ifndef ALGORITHM_LESSONPLANSCHEDULINGPROBLEMPROPERTIES_HPP
#define ALGORITHM_LESSONPLANSCHEDULINGPROBLEMPROPERTIES_HPP

#include <utility>
#include <vector>

using std::vector;

namespace lessonplans {
    class LessonplanSchedulingProblemProperties {
    public:
        LessonplanSchedulingProblemProperties(
                unsigned short weekDaysCount, unsigned short lessonsCount, unsigned short classesCount,
                unsigned short subjectsCount, unsigned short teachersCount, unsigned short roomsCount,
                vector<vector<unsigned short>> classesSubjects,
                vector<vector<unsigned short>> teachersSubjects,
                vector<vector<unsigned short>> roomsSubjects,
                vector<vector<unsigned short>> classesSubjectsCount
        ) :
                weekDaysCount(weekDaysCount), lessonsCount(lessonsCount),
                classesCount(classesCount), subjectsCount(subjectsCount),
                teachersCount(teachersCount), roomsCount(roomsCount),
                classesSubjects(std::move(classesSubjects)),
                teachersSubjects(std::move(teachersSubjects)),
                roomsSubjects(std::move(roomsSubjects)),
                classesSubjectsCount(std::move(classesSubjectsCount)) {}

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

        const vector<vector<unsigned short>> &getClassesSubjectsCount() const;

        const vector<unsigned short> &getClassSubjectsCount(unsigned short classIdx) const;

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
        vector<vector<unsigned short>> classesSubjectsCount;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULINGPROBLEMPROPERTIES_HPP
