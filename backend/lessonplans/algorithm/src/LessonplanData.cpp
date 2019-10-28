#include "LessonplanData.hpp"

#include <utility>

namespace lessonplans {

    unsigned short LessonplanData::getWeekDaysCount() const {
        return weekDaysCount;
    }

    unsigned short LessonplanData::getLessonsCount() const {
        return lessonsCount;
    }

    unsigned short LessonplanData::getClassesCount() const {
        return classesCount;
    }

    unsigned short LessonplanData::getSubjectsCount() const {
        return subjectsCount;
    }

    unsigned short LessonplanData::getTeachersCount() const {
        return teachersCount;
    }

    unsigned short LessonplanData::getRoomsCount() const {
        return roomsCount;
    }

    const vector <vector<unsigned short>> &LessonplanData::getClassesSubjects() const {
        return classesSubjects;
    }
    const vector<unsigned short> &LessonplanData::getClassSubjects(unsigned short classIdx) const {
        return this->getClassesSubjects()[classIdx];
    }

    const vector <vector<unsigned short>> &LessonplanData::getTeachersSubjects() const {
        return teachersSubjects;
    }
    const vector<unsigned short> &LessonplanData::getTeacherSubjects(unsigned short teacherIdx) const {
        return this->getTeachersSubjects()[teacherIdx];
    }

    const vector <vector<unsigned short>> &LessonplanData::getRoomsSubjects() const {
        return roomsSubjects;
    }
    const vector<unsigned short> &LessonplanData::getRoomSubjects(unsigned short roomIdx) const {
        return this->getRoomsSubjects()[roomIdx];
    }

    LessonplanData::LessonplanData(
        unsigned short weekDaysCount, unsigned short lessonsCount,
        unsigned short classesCount, unsigned short subjectsCount,
        unsigned short teachersCount, unsigned short roomsCount,
        vector<vector<unsigned short>> classesSubjects,
        vector<vector<unsigned short>> teachersSubjects,
        vector<vector<unsigned short>> roomsSubjects
    ) :
        weekDaysCount(weekDaysCount), lessonsCount(lessonsCount),
        classesCount(classesCount), subjectsCount(subjectsCount),
        teachersCount(teachersCount), roomsCount(roomsCount)
    {
        this->classesSubjects = std::move(classesSubjects);
        this->teachersSubjects = std::move(teachersSubjects);
        this->roomsSubjects = std::move(roomsSubjects);
    }

}