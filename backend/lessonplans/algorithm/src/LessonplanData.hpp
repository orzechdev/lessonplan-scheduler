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

        void setWeekDaysCount(unsigned short weekDaysCount);

        unsigned short getLessonsCount() const;

        void setLessonsCount(unsigned short lessonsCount);

        unsigned short getClassesCount() const;

        void setClassesCount(unsigned short classesCount);

        unsigned short getSubjectsCount() const;

        void setSubjectsCount(unsigned short subjectsCount);

        unsigned short getTeachersCount() const;

        void setTeachersCount(unsigned short teachersCount);

        unsigned short getRoomsCount() const;

        void setRoomsCount(unsigned short roomsCount);

        const vector<unsigned short> &getClassesSubjectsRestrictionStatus() const;

        void setClassesSubjectsRestrictionStatus(const vector<unsigned short> &classesSubjectsRestrictionStatus);

        const vector<vector<unsigned short>> &getClassesSubjects() const;

        void setClassesSubjects(const vector<vector<unsigned short>> &classesSubjects);

        const vector<unsigned short> &getTeachersSubjectsRestrictionStatus() const;

        void setTeachersSubjectsRestrictionStatus(const vector<unsigned short> &teachersSubjectsRestrictionStatus);

        const vector<vector<unsigned short>> &getTeachersSubjects() const;

        void setTeachersSubjects(const vector<vector<unsigned short>> &teachersSubjects);

        const vector<unsigned short> &getRoomsSubjectsRestrictionStatus() const;

        void setRoomsSubjectsRestrictionStatus(const vector<unsigned short> &roomsSubjectsRestrictionStatus);

        const vector<vector<unsigned short>> &getRoomsSubjects() const;

        void setRoomsSubjects(const vector<vector<unsigned short>> &roomsSubjects);

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
