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

    const vector<vector<unsigned short>> &LessonplanSchedulingProblemProperties::getClassesSubjects() const {
        return classesSubjects;
    }

    const vector<unsigned short> &
    LessonplanSchedulingProblemProperties::getClassSubjects(unsigned short classIdx) const {
        return this->getClassesSubjects()[classIdx];
    }

    const vector<vector<unsigned short>> &LessonplanSchedulingProblemProperties::getTeachersSubjects() const {
        return teachersSubjects;
    }

    const vector<unsigned short> &
    LessonplanSchedulingProblemProperties::getTeacherSubjects(unsigned short teacherIdx) const {
        return this->getTeachersSubjects()[teacherIdx];
    }

    const vector<vector<unsigned short>> &LessonplanSchedulingProblemProperties::getRoomsSubjects() const {
        return roomsSubjects;
    }

    const vector<unsigned short> &
    LessonplanSchedulingProblemProperties::getRoomSubjects(unsigned short roomIdx) const {
        return this->getRoomsSubjects()[roomIdx];
    }

    const vector<vector<unsigned short>> &LessonplanSchedulingProblemProperties::getClassesSubjectsCount() const {
        return classesSubjectsCount;
    }

    const vector<unsigned short> &
    LessonplanSchedulingProblemProperties::getClassSubjectsCount(unsigned short classIdx) const {
        return this->getClassesSubjectsCount()[classIdx];
    }

}