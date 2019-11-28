#include "../../include/lessonplan/LessonplanIndividual.hpp"

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

    LessonplanIndividualDescriptor *LessonplanIndividual::getLessonplanIndividualDescriptor() const {
        return lessonplanIndividualDescriptor;
    }

    void LessonplanIndividual::setLessonplanIndividualDescriptor(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor) {
        this->lessonplanIndividualDescriptor = lessonplanIndividualDescriptor;
    }


}