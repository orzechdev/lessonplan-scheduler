#include "../include/algorithm/LessonplanSchedulingProblemProperties.hpp"

#include <utility>

namespace lessonplans {

    unsigned short LessonplanSchedulingProblemProperties::getWeekDaysCount() const {
        return weekDaysCount;
    }

    unsigned short LessonplanSchedulingProblemProperties::getLessonsCount() const {
        return lessonsCount;
    }

    unsigned short LessonplanSchedulingProblemProperties::getClassesCount() const {
        return classesCount;
    }

    unsigned short LessonplanSchedulingProblemProperties::getSubjectsCount() const {
        return subjectsCount;
    }

    unsigned short LessonplanSchedulingProblemProperties::getTeachersCount() const {
        return teachersCount;
    }

    unsigned short LessonplanSchedulingProblemProperties::getRoomsCount() const {
        return roomsCount;
    }

    const vector <vector<unsigned short>> &LessonplanSchedulingProblemProperties::getClassesSubjects() const {
        return classesSubjects;
    }
    const vector<unsigned short> &LessonplanSchedulingProblemProperties::getClassSubjects(unsigned short classIdx) const {
        return this->getClassesSubjects()[classIdx];
    }

    const vector <vector<unsigned short>> &LessonplanSchedulingProblemProperties::getTeachersSubjects() const {
        return teachersSubjects;
    }
    const vector<unsigned short> &LessonplanSchedulingProblemProperties::getTeacherSubjects(unsigned short teacherIdx) const {
        return this->getTeachersSubjects()[teacherIdx];
    }

    const vector <vector<unsigned short>> &LessonplanSchedulingProblemProperties::getRoomsSubjects() const {
        return roomsSubjects;
    }
    const vector<unsigned short> &LessonplanSchedulingProblemProperties::getRoomSubjects(unsigned short roomIdx) const {
        return this->getRoomsSubjects()[roomIdx];
    }

    LessonplanSchedulingProblemProperties::LessonplanSchedulingProblemProperties(
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