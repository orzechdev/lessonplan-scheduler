#include "LessonplanIndividual.hpp"

#include <utility>
#include <random>
#include <algorithm>
#include <chrono>


namespace lessonplans {

    vector<vector<unsigned short>> LessonplanIndividual::getLessonplan() {
        return this->lessonplan;
    }

    void LessonplanIndividual::setLessonplan(vector<vector<unsigned short>> lessonplan) {
        LessonplanIndividual::lessonplan = std::move(lessonplan);
    }

    unsigned int LessonplanIndividual::getMaxDataCount() const {
        return maxDataCount;
    }

    void LessonplanIndividual::setMaxDataCount(unsigned int maxDataCount) {
        LessonplanIndividual::maxDataCount = maxDataCount;
    }

    unsigned short LessonplanIndividual::getAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx,
                                                                        unsigned short currentLessonIdx,
                                                                        unsigned short classIdx) const {
        return this->assignedLessonAndDaysToClasses[currentWeekDayIdx][currentLessonIdx][classIdx];
    }

    void LessonplanIndividual::setAssignedLessonAndDaysToClasses(
            vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses) {
        this->assignedLessonAndDaysToClasses = std::move(assignedLessonAndDaysToClasses);
    }

    void LessonplanIndividual::setAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx,
                                                              unsigned short currentLessonIdx,
                                                              unsigned short classIdx) {
        this->assignedLessonAndDaysToClasses[currentWeekDayIdx][currentLessonIdx][classIdx] = 1;
    }

    unsigned short LessonplanIndividual::getAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx,
                                                                          unsigned short currentLessonIdx,
                                                                          unsigned short teacherIdx) const {
        return this->assignedLessonAndDaysToTeachers[currentWeekDayIdx][currentLessonIdx][teacherIdx];
    }

    void LessonplanIndividual::setAssignedLessonAndDaysToTeachers(
            vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers) {
        this->assignedLessonAndDaysToTeachers = std::move(assignedLessonAndDaysToTeachers);
    }

    void LessonplanIndividual::setAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx,
                                                                unsigned short currentLessonIdx,
                                                                unsigned short teacherIdx) {
        this->assignedLessonAndDaysToTeachers[currentWeekDayIdx][currentLessonIdx][teacherIdx] = 1;
    }

    unsigned short LessonplanIndividual::getAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx,
                                                                       unsigned short currentLessonIdx,
                                                                       unsigned short roomIdx) const {
        return this->assignedLessonAndDaysToRooms[currentWeekDayIdx][currentLessonIdx][roomIdx];
    }

    void LessonplanIndividual::setAssignedLessonAndDaysToRooms(
            vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms) {
        this->assignedLessonAndDaysToRooms = std::move(assignedLessonAndDaysToRooms);
    }

    void LessonplanIndividual::setAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx,
                                                             unsigned short currentLessonIdx, unsigned short roomIdx) {
        this->assignedLessonAndDaysToRooms[currentWeekDayIdx][currentLessonIdx][roomIdx] = 1;
    }

    void LessonplanIndividual::setLessonplanDataItem(
            unsigned short dataIdx, unsigned short weekDayId, unsigned short lessonId,
            unsigned short classId, unsigned short subjectId,
            unsigned short teacherId, unsigned short roomId) {
        this->lessonplan[dataIdx][0] = weekDayId;
        this->lessonplan[dataIdx][1] = lessonId;
        this->lessonplan[dataIdx][2] = classId;
        this->lessonplan[dataIdx][3] = subjectId;
        this->lessonplan[dataIdx][4] = teacherId;
        this->lessonplan[dataIdx][5] = roomId;
    }

    void LessonplanIndividual::setLessonplanDataItemWeekDay(unsigned short dataIdx, unsigned short weekDayId) {
        this->lessonplan[dataIdx][0] = weekDayId;
    }

    void LessonplanIndividual::setLessonplanDataItemLesson(unsigned short dataIdx, unsigned short lessonId) {
        this->lessonplan[dataIdx][1] = lessonId;
    }

    void LessonplanIndividual::setLessonplanDataItemTeacher(unsigned short dataIdx, unsigned short teacherId) {
        this->lessonplan[dataIdx][4] = teacherId;
    }

    void LessonplanIndividual::setLessonplanDataItemRoom(unsigned short dataIdx, unsigned short roomId) {
        this->lessonplan[dataIdx][5] = roomId;
    }

}