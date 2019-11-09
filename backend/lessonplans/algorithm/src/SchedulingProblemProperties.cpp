#include "../include/algorithm/SchedulingProblemProperties.hpp"

#include <utility>

namespace lessonplans {

    unsigned short SchedulingProblemProperties::getWeekDaysCount() const {
        return weekDaysCount;
    }

    unsigned short SchedulingProblemProperties::getLessonsCount() const {
        return lessonsCount;
    }

    unsigned short SchedulingProblemProperties::getClassesCount() const {
        return classesCount;
    }

    unsigned short SchedulingProblemProperties::getSubjectsCount() const {
        return subjectsCount;
    }

    unsigned short SchedulingProblemProperties::getTeachersCount() const {
        return teachersCount;
    }

    unsigned short SchedulingProblemProperties::getRoomsCount() const {
        return roomsCount;
    }

    const vector<vector<unsigned short>> &SchedulingProblemProperties::getClassesSubjects() const {
        return classesSubjects;
    }

    const vector<unsigned short> &
    SchedulingProblemProperties::getClassSubjects(unsigned short classIdx) const {
        return this->getClassesSubjects()[classIdx];
    }

    const vector<vector<unsigned short>> &SchedulingProblemProperties::getTeachersSubjects() const {
        return teachersSubjects;
    }

    const vector<unsigned short> &
    SchedulingProblemProperties::getTeacherSubjects(unsigned short teacherIdx) const {
        return this->getTeachersSubjects()[teacherIdx];
    }

    const vector<vector<unsigned short>> &SchedulingProblemProperties::getRoomsSubjects() const {
        return roomsSubjects;
    }

    const vector<unsigned short> &
    SchedulingProblemProperties::getRoomSubjects(unsigned short roomIdx) const {
        return this->getRoomsSubjects()[roomIdx];
    }

    const vector<vector<unsigned short>> &SchedulingProblemProperties::getClassesSubjectsCount() const {
        return classesSubjectsCount;
    }

    const vector<unsigned short> &
    SchedulingProblemProperties::getClassSubjectsCount(unsigned short classIdx) const {
        return this->getClassesSubjectsCount()[classIdx];
    }

}