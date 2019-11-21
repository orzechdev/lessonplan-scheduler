#include <algorithm>
#include "../include/algorithm/SchedulingGreedyAlgorithm.hpp"
#include "RandomNumberGenerator.hpp"

namespace lessonplans {

    SchedulingGreedyAlgorithm::SchedulingGreedyAlgorithm(int iterationsCount) {
        this->iterationsCount = iterationsCount;

        this->individualsHardScores = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::scoresTypesImportant
                )
        );
        this->individualsSoftScores = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::scoresTypesOptimal
                )
        );
        this->individualsSummaryHardScores = *new vector<int>(
                this->iterationsCount
        );
        this->individualsSummarySoftScores = *new vector<int>(
                this->iterationsCount
        );
    }

    SchedulingSolution *SchedulingGreedyAlgorithm::findBestLessonplan(SchedulingProblem *schedulingProblem) {
        this->bestIndividual = schedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(this->bestIndividual);

        this->individualsHardScores[0] = obtainedScores[0];
        this->individualsSoftScores[0] = obtainedScores[1];

        this->individualsSummaryHardScores[0] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores[0]);
        this->individualsSummarySoftScores[0] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores[1]);

        int bestIndividualIdx = 0;

        for (int i = 1; i < this->iterationsCount; i++) {
            LessonplanIndividual *currentIndividual = this->reformLessonplan(this->bestIndividual, schedulingProblem);
            obtainedScores = schedulingProblem->evaluateLessonplan(currentIndividual);

            this->individualsHardScores[i] = obtainedScores[0];
            this->individualsSoftScores[i] = obtainedScores[1];

            this->individualsSummaryHardScores[i] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores[0]);
            this->individualsSummarySoftScores[i] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores[1]);

            bestIndividualIdx = i;
            this->bestIndividual = currentIndividual;


//            // Compare scores in greedy way:
//            // choose best move in currently occurred situation, i.e. first maximize hard score, and just after then
//            // maximize soft score - it might be not be the best chosen path, although it is the greedy chosen path,
//            // the best from individual perspective
//            if (this->individualsSummaryHardScores[i] == this->individualsSummaryHardScores[bestIndividualIdx]) {
//                if (this->individualsSummarySoftScores[i] > this->individualsSummarySoftScores[bestIndividualIdx]) {
//                    bestIndividualIdx = i;
//                    this->bestIndividual = currentIndividual;
//                }
//            } else if (this->individualsSummaryHardScores[i] > this->individualsSummaryHardScores[bestIndividualIdx]) {
//                bestIndividualIdx = i;
//                this->bestIndividual = currentIndividual;
//            }
        }

        auto *lessonplanSchedulingSoultion = new SchedulingSolution(
                this->bestIndividual,
                this->individualsHardScores,
                this->individualsSoftScores,
                this->individualsSummaryHardScores
        );

        return lessonplanSchedulingSoultion;
    }

    LessonplanIndividual *SchedulingGreedyAlgorithm::reformLessonplan(LessonplanIndividual *lessonplanIndividual,
                                                                      SchedulingProblem *schedulingProblem) {
        /*
         * Class is const
         * Subject is const
         *
         * Weekday may change
         * Lesson may change
         * Teacher may change (but for each class and subject pair it must be always the same)
         * Room may change
         */

        SchedulingProblemProperties *schedulingProblemProperties = schedulingProblem->getSchedulingProblemProperties();

        LessonplanIndividualDescriptor *lessonplanIndividualDescriptor = lessonplanIndividual->getLessonplanIndividualDescriptor();
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers = lessonplanIndividualDescriptor->getAssignedLessonAndDaysToTeachers();
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms = lessonplanIndividualDescriptor->getAssignedLessonAndDaysToRooms();
        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses = lessonplanIndividualDescriptor->getAssignedLessonAndDaysToClasses();

        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();

        vector<unsigned short> dataItemIdxsSequence = RandomNumberGenerator::getRandomIdxsSequence(maxDataCount);

        for (unsigned int dataIdxNum = 0; dataIdxNum < maxDataCount; dataIdxNum++) {
            unsigned short dataIdx = dataItemIdxsSequence[dataIdxNum];

            vector<unsigned short> *lessonplanDataItem = &lessonplan[dataIdx];

            this->reformLessonplanTeacherDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                                  lessonplanDataItem, &assignedLessonAndDaysToTeachers);
            this->reformLessonplanRoomDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                               lessonplanDataItem, &assignedLessonAndDaysToRooms);
            this->reformLessonplanClassSubjectDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                                       lessonplanDataItem, &assignedLessonAndDaysToClasses);

            lessonplanIndividual->setLessonplan(lessonplan);
            schedulingProblem->evaluateLessonplan(lessonplanIndividual);
        }

        lessonplanIndividual->setLessonplan(lessonplan);
//        lessonplanIndividualDescriptor->setAssignedLessonAndDaysToTeachers(assignedLessonAndDaysToTeachers);
//        lessonplanIndividualDescriptor->setAssignedLessonAndDaysToRooms(assignedLessonAndDaysToRooms);
//        lessonplanIndividualDescriptor->setAssignedLessonAndDaysToClasses(assignedLessonAndDaysToClasses);

        return lessonplanIndividual;
    }


    void SchedulingGreedyAlgorithm::reformLessonplanTeacherDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem,
            vector<vector<vector<unsigned short>>> *assignedLessonAndDaysToTeachers) {

        unsigned short teachersCount = schedulingProblemProperties->getTeachersCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short teacherIdx = (*lessonplanDataItem)[4] - 1;

        unsigned short prevAssignedLessonAndDayToTeacher = lessonplanIndividualDescriptor->getAssignedLessonAndDayToTeacher(
                weekDayIdx, lessonIdx, teacherIdx);

        if (prevAssignedLessonAndDayToTeacher > 1) {
            unsigned short teacherIdToChange = RandomNumberGenerator::getRandomNumber(1, teachersCount);

            prevAssignedLessonAndDayToTeacher--;
            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);
//            (*assignedLessonAndDaysToTeachers)[weekDayIdx][lessonIdx][teacherIdx]--;

            (*lessonplanDataItem)[4] = teacherIdToChange;
            unsigned short teacherIdxToChange = teacherIdToChange - 1;

//            (*assignedLessonAndDaysToTeachers)[weekDayIdx][lessonIdx][teacherIdxToChange]++;
            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx,
                                                                                  teacherIdxToChange);
        }
    }

    void SchedulingGreedyAlgorithm::reformLessonplanRoomDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem,
            vector<vector<vector<unsigned short>>> *assignedLessonAndDaysToRooms) {
        unsigned short roomsCount = schedulingProblemProperties->getRoomsCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short roomIdx = (*lessonplanDataItem)[5] - 1;

        unsigned short prevAssignedLessonAndDayToRoom = lessonplanIndividualDescriptor->getAssignedLessonAndDayToRoom(
                weekDayIdx, lessonIdx, roomIdx);

        if (prevAssignedLessonAndDayToRoom > 1) {
            unsigned short roomIdToChange = RandomNumberGenerator::getRandomNumber(1, roomsCount);

            prevAssignedLessonAndDayToRoom--;
//            (*assignedLessonAndDaysToRooms)[weekDayIdx][lessonIdx][roomIdx]--;
            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

            (*lessonplanDataItem)[5] = roomIdToChange;
            unsigned short roomIdxToChange = roomIdToChange - 1;

//            (*assignedLessonAndDaysToRooms)[weekDayIdx][lessonIdx][roomIdxToChange]++;
            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdxToChange);
        }
    }

    void SchedulingGreedyAlgorithm::reformLessonplanClassSubjectDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem,
            vector<vector<vector<unsigned short>>> *assignedLessonAndDaysToClasses) {
        unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
        unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short classIdx = (*lessonplanDataItem)[2] - 1;

        unsigned short prevAssignedLessonAndDayToClass = lessonplanIndividualDescriptor->getAssignedLessonAndDayToClass(
                weekDayIdx, lessonIdx, classIdx);
        unsigned short classStartLessonsDifferenceCountAverage = lessonplanIndividualDescriptor->getClassesStartLessonsDifferenceCountAverage()[classIdx];
        unsigned short classLessonsCountDifferenceBetweenDaysAverage = lessonplanIndividualDescriptor->getClassesLessonsCountAverageDifferenceBetweenDays()[classIdx];
        unsigned short classFreePeriodsExistenceBetweenLessonsCount = lessonplanIndividualDescriptor->getClassesFreePeriodsExistenceBetweenLessonsCount()[classIdx];

        if (prevAssignedLessonAndDayToClass > 1 ||
            classStartLessonsDifferenceCountAverage > 1 ||
            classLessonsCountDifferenceBetweenDaysAverage > 1 ||
            classFreePeriodsExistenceBetweenLessonsCount > 0) {
            for (unsigned short lessonIdxToChange = 0; lessonIdxToChange < lessonsCount; lessonIdxToChange++) {
                vector<unsigned short> weekDaysIdxsSequence = RandomNumberGenerator::getRandomIdxsSequence(weekDaysCount);
                for (unsigned short weekDayIdxNum = 0; weekDayIdxNum < weekDaysCount; weekDayIdxNum++) {
                    unsigned short weekDayIdxToChange = weekDaysIdxsSequence[weekDayIdxNum];
                    unsigned short anotherAssignedLessonAndDayToClass = lessonplanIndividualDescriptor->getAssignedLessonAndDayToClass(
                            weekDayIdxToChange, lessonIdxToChange, classIdx);

                    if (anotherAssignedLessonAndDayToClass <= 0) {

                        lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToClass(weekDayIdx, lessonIdx,
                                                                                            classIdx);

                        (*lessonplanDataItem)[0] = weekDayIdxToChange + 1;
                        (*lessonplanDataItem)[1] = lessonIdxToChange + 1;

                        lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(weekDayIdxToChange,
                                                                                            lessonIdxToChange,
                                                                                            classIdx);
                        return;
                    }
                }
            }
        }


        /*
         * TODO: add additional reform based on score evaluated for individual
         */
    }

    int SchedulingGreedyAlgorithm::getSummaryScore(
            vector<int> obtainedScores
    ) {
        int summaryGrade = 0;
        std::for_each(obtainedScores.begin(), obtainedScores.end(), [&](int grade) {
            summaryGrade += grade;
        });
        return summaryGrade;
    }

}
