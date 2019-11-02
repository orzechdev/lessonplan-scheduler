#include <cstdlib>
#include "../include/algorithm/LessonplanSchedulingProblem.hpp"
#include "LessonplanIndividualAbstractFactory.hpp"

namespace lessonplans {

    LessonplanIndividual* LessonplanSchedulingProblem::getSampleLessonplan(){
        LessonplanIndividual* lessonplanIndividual = LessonplanIndividualAbstractFactory::createLessonplanIndividual(this->lessonplanSchedulingProblemProperties);

        return lessonplanIndividual;
    }

    vector<int> LessonplanSchedulingProblem::evaluateLessonplan(LessonplanIndividual* lessonplanIndividual) {
        //-1pt - for each lesson deviated from lessons in other days
        unsigned short invalidDifferenceBetweenStartLessons = this->checkStartLessonsDifferenceBetweenDays(lessonplanIndividual);

        //-1pt - for each deviated hour between the days of the week
        unsigned short invalidDifferenceBetweenLessonsCount = this->checkLessonsCountDifferenceBetweenDays(lessonplanIndividual);

        //-1pt - for each free period between lessons
        unsigned short invalidFreePeriodsCountBetweenLessons = this->checkFreePeriodsExistenceBetweenLessons(lessonplanIndividual);

        vector<int> grades = *new vector<int>(LessonplanSchedulingProblem::scoresTypes);

        grades[0] = 0 - invalidDifferenceBetweenStartLessons;
        grades[1] = 0 - invalidDifferenceBetweenLessonsCount;
        grades[2] = 0 - invalidFreePeriodsCountBetweenLessons;

        return grades;
    }

    unsigned short LessonplanSchedulingProblem::checkStartLessonsDifferenceBetweenDays(
            LessonplanIndividual* lessonplanIndividual
    ) {
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
        unsigned short classesCount = this->lessonplanSchedulingProblemProperties->getClassesCount();
        unsigned short weekDaysCount = this->lessonplanSchedulingProblemProperties->getWeekDaysCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();

        vector<vector<unsigned short>> classesWeekDayStartLessonId = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );

        for(unsigned int dataIdx = 0; dataIdx < maxDataCount; dataIdx++) {
            unsigned short weekDayId = lessonplan[dataIdx][0];
            unsigned short lessonId = lessonplan[dataIdx][1];
            unsigned short classId = lessonplan[dataIdx][2];

            unsigned short classWeekDayStartLessonId = classesWeekDayStartLessonId[classId - 1][weekDayId - 1];

            if (classWeekDayStartLessonId == 0) {
                classesWeekDayStartLessonId[classId - 1][weekDayId - 1] = lessonId;
                continue;
            }

            if (lessonId < classWeekDayStartLessonId) {
                classesWeekDayStartLessonId[classId - 1][weekDayId - 1] = lessonId;
            }
        }

        unsigned short startLessonsDifferencesCount = 0;

        for(unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short classDifferencesCountForAllWeekDays = 0;
            unsigned short weekDaysWithoutLessons = 0;

            for(unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short startLessonIdInAnotherDay = classesWeekDayStartLessonId[classIdx][weekDayIdx];

                if (startLessonIdInAnotherDay == 0) {
                    weekDaysWithoutLessons++;
                } else {
                    for(unsigned short weekDayIdx2 = 0; weekDayIdx2 < weekDaysCount; weekDayIdx2++) {
                        unsigned short startLessonIdInAnotherDay2 = classesWeekDayStartLessonId[classIdx][weekDayIdx2];

                        if (startLessonIdInAnotherDay2 == 0) {
                            classDifferencesCountForAllWeekDays += abs(startLessonIdInAnotherDay - startLessonIdInAnotherDay2);
                        }
                    }
                }
            }

            unsigned short availableWeekDays = weekDaysCount - weekDaysWithoutLessons;
            if (availableWeekDays != 0) {
                auto classDifferencesCountAverage = static_cast<unsigned short>(classDifferencesCountForAllWeekDays / availableWeekDays);
                startLessonsDifferencesCount += classDifferencesCountAverage;
            }
        }

        return startLessonsDifferencesCount;
    }

    unsigned short LessonplanSchedulingProblem::checkLessonsCountDifferenceBetweenDays(
            LessonplanIndividual* lessonplanIndividual
    ) {
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
        unsigned short classesCount = this->lessonplanSchedulingProblemProperties->getClassesCount();
        unsigned short weekDaysCount = this->lessonplanSchedulingProblemProperties->getWeekDaysCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();

        vector<vector<unsigned short>> classesWeekDayLessonsCount = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );

        for(unsigned int dataIdx = 0; dataIdx < maxDataCount; dataIdx++) {
            unsigned short weekDayId = lessonplan[dataIdx][0];
            unsigned short classId = lessonplan[dataIdx][2];

            classesWeekDayLessonsCount[classId - 1][weekDayId - 1]++;
        }

        unsigned short lessonsDifferencesCount = 0;

        for(unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short classDifferencesCountForAllWeekDays = 0;

            for(unsigned short weekDayIdx = 1; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short lessonsCountInAnotherDay = classesWeekDayLessonsCount[classIdx][weekDayIdx];

                for(unsigned short weekDayIdx2 = 0; weekDayIdx2 < weekDaysCount; weekDayIdx2++) {
                    unsigned short lessonsCountInAnotherDay2 = classesWeekDayLessonsCount[classIdx][weekDayIdx2];

                    classDifferencesCountForAllWeekDays += abs(lessonsCountInAnotherDay - lessonsCountInAnotherDay2);
                }
            }

            auto classDifferencesCountAverage = static_cast<unsigned short>(classDifferencesCountForAllWeekDays / weekDaysCount);
            lessonsDifferencesCount += classDifferencesCountAverage;
        }

        return lessonsDifferencesCount;
    }

    unsigned short LessonplanSchedulingProblem::checkFreePeriodsExistenceBetweenLessons(
            LessonplanIndividual *lessonplanIndividual
    ) {
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
        unsigned short classesCount = this->lessonplanSchedulingProblemProperties->getClassesCount();
        unsigned short weekDaysCount = this->lessonplanSchedulingProblemProperties->getWeekDaysCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();

        vector<vector<unsigned short>> classesWeekDayStartLessonId = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );
        vector<vector<unsigned short>> classesWeekDayEndLessonId = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );

        vector<vector<unsigned short>> classesWeekDayFreePeriods = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        weekDaysCount, 0
                )
        );

        for(unsigned int dataIdx = 0; dataIdx < maxDataCount; dataIdx++) {
            unsigned short weekDayId = lessonplan[dataIdx][0];
            unsigned short lessonId = lessonplan[dataIdx][1];
            unsigned short classId = lessonplan[dataIdx][2];

            unsigned short classWeekDayStartLessonId = classesWeekDayStartLessonId[classId - 1][weekDayId - 1];
            unsigned short classWeekDayEndLessonId = classesWeekDayEndLessonId[classId - 1][weekDayId - 1];

            if (classWeekDayStartLessonId == 0) {
                classesWeekDayStartLessonId[classId - 1][weekDayId - 1] = lessonId;
                classesWeekDayEndLessonId[classId - 1][weekDayId - 1] = lessonId;
                continue;
            }

            if (lessonId < classWeekDayStartLessonId) {
                classesWeekDayStartLessonId[classId - 1][weekDayId - 1] = lessonId;
                unsigned short lessonsDifference = classWeekDayStartLessonId - lessonId;

                if (lessonsDifference > 1) {
                    classesWeekDayFreePeriods[classId - 1][weekDayId - 1] += lessonsDifference - 1;
                }
            } else if (lessonId > classWeekDayEndLessonId) {
                classesWeekDayEndLessonId[classId - 1][weekDayId - 1] = lessonId;
                unsigned short lessonsDifference = lessonId - classWeekDayEndLessonId;

                if (lessonsDifference > 1) {
                    classesWeekDayFreePeriods[classId - 1][weekDayId - 1] += lessonsDifference - 1;
                }
            } else {
                classesWeekDayFreePeriods[classId - 1][weekDayId - 1]--;
            }

        }

        unsigned short classesFreePeriodsCount = 0;

        for(unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            for(unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short freePeriodsCountInAnotherDay = classesWeekDayFreePeriods[classIdx][weekDayIdx];

                classesFreePeriodsCount += freePeriodsCountInAnotherDay;
            }
        }

        return classesFreePeriodsCount;
    }

}