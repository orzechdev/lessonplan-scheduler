#include "../../include/lessonplan/LessonplanIndividualDescriptor.hpp"

namespace lessonplans {

    vector<vector<vector<unsigned short>>> LessonplanIndividualDescriptor::getAssignedLessonAndDaysToClasses() const {
        return this->assignedLessonAndDaysToClasses;
    }

    vector<vector<vector<unsigned short>>> LessonplanIndividualDescriptor::getAssignedLessonAndDaysToTeachers() const {
        return this->assignedLessonAndDaysToTeachers;
    }

    vector<vector<vector<unsigned short>>> LessonplanIndividualDescriptor::getAssignedLessonAndDaysToRooms() const {
        return this->assignedLessonAndDaysToRooms;
    }

    unsigned short LessonplanIndividualDescriptor::getAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx,
                                                                                  unsigned short currentLessonIdx,
                                                                                  unsigned short classIdx) const {
        return this->assignedLessonAndDaysToClasses[currentWeekDayIdx][currentLessonIdx][classIdx];
    }

    void LessonplanIndividualDescriptor::setAssignedLessonAndDaysToClasses(
            vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses) {
        this->assignedLessonAndDaysToClasses = std::move(assignedLessonAndDaysToClasses);
    }

    void LessonplanIndividualDescriptor::increaseAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx,
                                                                             unsigned short currentLessonIdx,
                                                                             unsigned short classIdx) {
        this->assignedLessonAndDaysToClasses[currentWeekDayIdx][currentLessonIdx][classIdx]++;
    }

    void LessonplanIndividualDescriptor::decreaseAssignedLessonAndDayToClass(unsigned short currentWeekDayIdx,
                                                                             unsigned short currentLessonIdx,
                                                                             unsigned short classIdx) {
        this->assignedLessonAndDaysToClasses[currentWeekDayIdx][currentLessonIdx][classIdx]--;
    }

    unsigned short LessonplanIndividualDescriptor::getAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx,
                                                                                    unsigned short currentLessonIdx,
                                                                                    unsigned short teacherIdx) const {
        return this->assignedLessonAndDaysToTeachers[currentWeekDayIdx][currentLessonIdx][teacherIdx];
    }

    void LessonplanIndividualDescriptor::setAssignedLessonAndDaysToTeachers(
            vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers) {
        this->assignedLessonAndDaysToTeachers = std::move(assignedLessonAndDaysToTeachers);
    }

    void LessonplanIndividualDescriptor::increaseAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx,
                                                                               unsigned short currentLessonIdx,
                                                                               unsigned short teacherIdx) {
        this->assignedLessonAndDaysToTeachers[currentWeekDayIdx][currentLessonIdx][teacherIdx]++;
    }

    void LessonplanIndividualDescriptor::decreaseAssignedLessonAndDayToTeacher(unsigned short currentWeekDayIdx,
                                                                               unsigned short currentLessonIdx,
                                                                               unsigned short teacherIdx) {
        this->assignedLessonAndDaysToTeachers[currentWeekDayIdx][currentLessonIdx][teacherIdx]--;
    }

    unsigned short LessonplanIndividualDescriptor::getAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx,
                                                                                 unsigned short currentLessonIdx,
                                                                                 unsigned short roomIdx) const {
        return this->assignedLessonAndDaysToRooms[currentWeekDayIdx][currentLessonIdx][roomIdx];
    }

    void LessonplanIndividualDescriptor::setAssignedLessonAndDaysToRooms(
            vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms) {
        this->assignedLessonAndDaysToRooms = std::move(assignedLessonAndDaysToRooms);
    }

    void LessonplanIndividualDescriptor::increaseAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx,
                                                                            unsigned short currentLessonIdx,
                                                                            unsigned short roomIdx) {
        this->assignedLessonAndDaysToRooms[currentWeekDayIdx][currentLessonIdx][roomIdx]++;
    }

    void LessonplanIndividualDescriptor::decreaseAssignedLessonAndDayToRoom(unsigned short currentWeekDayIdx,
                                                                            unsigned short currentLessonIdx,
                                                                            unsigned short roomIdx) {
        this->assignedLessonAndDaysToRooms[currentWeekDayIdx][currentLessonIdx][roomIdx]--;
    }

    vector<unsigned short> LessonplanIndividualDescriptor::getClassesStartLessonsDifferenceCountAverage() const {
        return this->classesStartLessonsDifferenceCountAverage;
    }

    void LessonplanIndividualDescriptor::setClassesStartLessonsDifferenceCountAverage(
            vector<unsigned short> classesStartLessonsDifferenceCountAverage) {
        this->classesStartLessonsDifferenceCountAverage = classesStartLessonsDifferenceCountAverage;
    }

    vector<unsigned short> LessonplanIndividualDescriptor::getClassesLessonsCountAverageDifferenceBetweenDays() const {
        return this->classesLessonsCountAverageDifferenceBetweenDays;
    }

    void LessonplanIndividualDescriptor::setClassesLessonsCountAverageDifferenceBetweenDays(
            vector<unsigned short> classesLessonsCountAverageDifferenceBetweenDays) {
        this->classesLessonsCountAverageDifferenceBetweenDays = classesLessonsCountAverageDifferenceBetweenDays;
    }

    vector<unsigned short> LessonplanIndividualDescriptor::getClassesFreePeriodsExistenceBetweenLessonsCount() const {
        return this->classesFreePeriodsExistenceBetweenLessonsCount;
    }

    void LessonplanIndividualDescriptor::setClassesFreePeriodsExistenceBetweenLessonsCount(
            vector<unsigned short> classesFreePeriodsExistenceBetweenLessonsCount) {
        this->classesFreePeriodsExistenceBetweenLessonsCount = classesFreePeriodsExistenceBetweenLessonsCount;
    }

    vector<vector<unsigned short>>
    LessonplanIndividualDescriptor::getAssignedTeachersToClassesSubjectsWrong() const {
        return this->assignedTeachersToClassesSubjectsWrong;
    }

    unsigned short LessonplanIndividualDescriptor::getAssignedTeachersToClassSubjectWrong(unsigned short classIdx,
                                                                                          unsigned short subjectIdx) const {
        return this->assignedTeachersToClassesSubjectsWrong[classIdx][subjectIdx];
    }

    void LessonplanIndividualDescriptor::setAssignedTeachersToClassesSubjectsWrong(
            vector<vector<unsigned short>> assignedTeachersToClassesSubjectsWrong){
        this->assignedTeachersToClassesSubjectsWrong = assignedTeachersToClassesSubjectsWrong;
    }

    void LessonplanIndividualDescriptor::setAssignedTeachersToClassSubjectWrong(unsigned short classIdx,
                                                                                unsigned short subjectIdx,
                                                                                unsigned short isWrong) {
        this->assignedTeachersToClassesSubjectsWrong[classIdx][subjectIdx] = isWrong;
    }

}