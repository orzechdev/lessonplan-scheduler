#include "LessonplanData.hpp"

#include <utility>

namespace lessonplans {

    unsigned short LessonplanData::getWeekDaysCount() const {
        return weekDaysCount;
    }

    void LessonplanData::setWeekDaysCount(unsigned short weekDaysCount) {
        LessonplanData::weekDaysCount = weekDaysCount;
    }

    unsigned short LessonplanData::getLessonsCount() const {
        return lessonsCount;
    }

    void LessonplanData::setLessonsCount(unsigned short lessonsCount) {
        LessonplanData::lessonsCount = lessonsCount;
    }

    unsigned short LessonplanData::getClassesCount() const {
        return classesCount;
    }

    void LessonplanData::setClassesCount(unsigned short classesCount) {
        LessonplanData::classesCount = classesCount;
    }

    unsigned short LessonplanData::getSubjectsCount() const {
        return subjectsCount;
    }

    void LessonplanData::setSubjectsCount(unsigned short subjectsCount) {
        LessonplanData::subjectsCount = subjectsCount;
    }

    unsigned short LessonplanData::getTeachersCount() const {
        return teachersCount;
    }

    void LessonplanData::setTeachersCount(unsigned short teachersCount) {
        LessonplanData::teachersCount = teachersCount;
    }

    unsigned short LessonplanData::getRoomsCount() const {
        return roomsCount;
    }

    void LessonplanData::setRoomsCount(unsigned short roomsCount) {
        LessonplanData::roomsCount = roomsCount;
    }

    const vector<unsigned short> &LessonplanData::getClassesSubjectsRestrictionStatus() const {
        return classesSubjectsRestrictionStatus;
    }

    void LessonplanData::setClassesSubjectsRestrictionStatus(
            const vector<unsigned short> &classesSubjectsRestrictionStatus) {
        LessonplanData::classesSubjectsRestrictionStatus = classesSubjectsRestrictionStatus;
    }

    const vector <vector<unsigned short>> &LessonplanData::getClassesSubjects() const {
        return classesSubjects;
    }

    void LessonplanData::setClassesSubjects(const vector <vector<unsigned short>> &classesSubjects) {
        LessonplanData::classesSubjects = classesSubjects;
    }

    const vector<unsigned short> &LessonplanData::getTeachersSubjectsRestrictionStatus() const {
        return teachersSubjectsRestrictionStatus;
    }

    void LessonplanData::setTeachersSubjectsRestrictionStatus(
            const vector<unsigned short> &teachersSubjectsRestrictionStatus) {
        LessonplanData::teachersSubjectsRestrictionStatus = teachersSubjectsRestrictionStatus;
    }

    const vector <vector<unsigned short>> &LessonplanData::getTeachersSubjects() const {
        return teachersSubjects;
    }

    void
    LessonplanData::setTeachersSubjects(const vector <vector<unsigned short>> &teachersSubjects) {
        LessonplanData::teachersSubjects = teachersSubjects;
    }

    const vector<unsigned short> &LessonplanData::getRoomsSubjectsRestrictionStatus() const {
        return roomsSubjectsRestrictionStatus;
    }

    void LessonplanData::setRoomsSubjectsRestrictionStatus(
            const vector<unsigned short> &roomsSubjectsRestrictionStatus) {
        LessonplanData::roomsSubjectsRestrictionStatus = roomsSubjectsRestrictionStatus;
    }

    const vector <vector<unsigned short>> &LessonplanData::getRoomsSubjects() const {
        return roomsSubjects;
    }

    void LessonplanData::setRoomsSubjects(const vector <vector<unsigned short>> &roomsSubjects) {
        LessonplanData::roomsSubjects = roomsSubjects;
    }

    LessonplanData::LessonplanData(
        unsigned short weekDaysCount, unsigned short lessonsCount,
        unsigned short classesCount, unsigned short subjectsCount,
        unsigned short teachersCount, unsigned short roomsCount,
        vector<unsigned short> classesSubjectsRestrictionStatus,
        vector<vector<unsigned short>> classesSubjects,
        vector<unsigned short> teachersSubjectsRestrictionStatus,
        vector<vector<unsigned short>> teachersSubjects,
        vector<unsigned short> roomsSubjectsRestrictionStatus,
        vector<vector<unsigned short>> roomsSubjects
    ) :
        weekDaysCount(weekDaysCount), lessonsCount(lessonsCount),
        classesCount(classesCount), subjectsCount(subjectsCount),
        teachersCount(teachersCount), roomsCount(roomsCount)
    {
        this->classesSubjectsRestrictionStatus = std::move(classesSubjectsRestrictionStatus);
        this->classesSubjects = std::move(classesSubjects);
        this->teachersSubjectsRestrictionStatus = std::move(teachersSubjectsRestrictionStatus);
        this->teachersSubjects = std::move(teachersSubjects);
        this->roomsSubjectsRestrictionStatus = std::move(roomsSubjectsRestrictionStatus);
        this->roomsSubjects = std::move(roomsSubjects);
    }

}