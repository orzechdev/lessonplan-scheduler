#include "LessonplanSchedulingProblem.hpp"

namespace lessonplans {

    LessonplanIndividual* LessonplanSchedulingProblem::getSampleLessonplan(){
        auto* lessonplanIndividual = new LessonplanIndividual();

        lessonplanIndividual->initLessonplan(this->lessonplanData);

        return lessonplanIndividual;
    }

    int LessonplanSchedulingProblem::evaluateLessonplan(LessonplanIndividual* lessonplanIndividual) {
        //-1pt - for each class, which have too much deviated start lesson from lessons in other days
        unsigned short classesWithInvalidDifferenceBetweenStartLessons = this->checkStartLessonsDifferenceBetweenDays(lessonplanIndividual, 1);

        //-1pt - for each class, which have too much deviated number of hours between the days of the week
        unsigned short classesWithInvalidDifferenceBetweenLessonsCount = this->checkLessonsCountDifferenceBetweenDays(lessonplanIndividual, 1);

        //-1pt - for each free hour between lesson


        return 0 - classesWithInvalidDifferenceBetweenStartLessons - classesWithInvalidDifferenceBetweenLessonsCount;
    }

    unsigned short LessonplanSchedulingProblem::checkStartLessonsDifferenceBetweenDays(
            LessonplanIndividual* lessonplanIndividual, unsigned short maxValidStartLessonsDifferenceBetweenDays
    ) {
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
        unsigned short classesCount = this->lessonplanData->getClassesCount();
        unsigned short weekDaysCount = this->lessonplanData->getWeekDaysCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getIndividual();

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

        unsigned short classesWithFailedCheck = 0;

        for(unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short minStartLessonIdInEveryWeekDay, maxStartLessonIdInEveryWeekDay;
            minStartLessonIdInEveryWeekDay = maxStartLessonIdInEveryWeekDay = 0;

            for(unsigned short weekDayIdx = 0; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short startLessonIdInAnotherDay = classesWeekDayStartLessonId[classIdx][weekDayIdx];

                if (startLessonIdInAnotherDay == 0) {
                    continue;
                } else if (minStartLessonIdInEveryWeekDay == 0) {
                    minStartLessonIdInEveryWeekDay = maxStartLessonIdInEveryWeekDay = startLessonIdInAnotherDay;
                    continue;
                }

                if (startLessonIdInAnotherDay < minStartLessonIdInEveryWeekDay) {
                    minStartLessonIdInEveryWeekDay = startLessonIdInAnotherDay;
                } else if (startLessonIdInAnotherDay > maxStartLessonIdInEveryWeekDay) {
                    maxStartLessonIdInEveryWeekDay = startLessonIdInAnotherDay;
                }

                // Check if starting lesson between days differs more then maxValidStartLessonsDifferenceBetweenDays lesson
                if (maxStartLessonIdInEveryWeekDay - minStartLessonIdInEveryWeekDay > maxValidStartLessonsDifferenceBetweenDays) {
                    classesWithFailedCheck++;
                    break;
                }
            }
        }

        return classesWithFailedCheck;
    }

    unsigned short LessonplanSchedulingProblem::checkLessonsCountDifferenceBetweenDays(
            LessonplanIndividual* lessonplanIndividual, unsigned short maxValidLessonsCountDifferenceBetweenDays
    ) {
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
        unsigned short classesCount = this->lessonplanData->getClassesCount();
        unsigned short weekDaysCount = this->lessonplanData->getWeekDaysCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getIndividual();

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

        unsigned short classesWithFailedCheck = 0;

        for(unsigned short classIdx = 0; classIdx < classesCount; classIdx++) {
            unsigned short minLessonsCountInEveryWeekDay, maxLessonsCountInEveryWeekDay;
            minLessonsCountInEveryWeekDay = maxLessonsCountInEveryWeekDay = classesWeekDayLessonsCount[classIdx][0];

            for(unsigned short weekDayIdx = 1; weekDayIdx < weekDaysCount; weekDayIdx++) {
                unsigned short lessonsCountInAnotherDay = classesWeekDayLessonsCount[classIdx][weekDayIdx];

                if (lessonsCountInAnotherDay < minLessonsCountInEveryWeekDay) {
                    minLessonsCountInEveryWeekDay = lessonsCountInAnotherDay;
                } else if (lessonsCountInAnotherDay > maxLessonsCountInEveryWeekDay) {
                    maxLessonsCountInEveryWeekDay = lessonsCountInAnotherDay;
                }

                // Check if lessons count between days differs more then maxValidStartLessonsDifferenceBetweenDays lesson
                if (maxLessonsCountInEveryWeekDay - minLessonsCountInEveryWeekDay > maxValidLessonsCountDifferenceBetweenDays) {
                    classesWithFailedCheck++;
                    break;
                }
            }
        }

        return classesWithFailedCheck;
    }


}