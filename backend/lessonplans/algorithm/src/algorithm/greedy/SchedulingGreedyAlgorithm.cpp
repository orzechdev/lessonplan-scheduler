#include <algorithm>
#include <iostream>
#include <chrono>
#include "../../../include/algorithm/greedy/SchedulingGreedyAlgorithm.hpp"
#include "../../../include/utils/RandomNumberGenerator.hpp"
#include "../../../include/lessonplan/LessonplanScoreList.hpp"

namespace lessonplans {

    SchedulingGreedyAlgorithm::SchedulingGreedyAlgorithm(int calculationsTimeLimitInSeconds) {
        this->calculationsTimeLimitInSeconds = calculationsTimeLimitInSeconds;

        this->lessonplanScoreList = new LessonplanScoreList();
    }

    SchedulingSolution *SchedulingGreedyAlgorithm::findBestLessonplan(SchedulingProblem *schedulingProblem) {
        auto start = std::chrono::steady_clock::now();
        auto end = start;
        auto timeToWait = std::chrono::seconds(calculationsTimeLimitInSeconds);

        bestIndividual = schedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(bestIndividual);
        lessonplanScoreList->add(obtainedScores);

        while (end - start < timeToWait && (lessonplanScoreList->getLastSummaryHardScore() != 0 || lessonplanScoreList->getLastSummarySoftScore() != 0)) {
            reformLessonplan(bestIndividual, schedulingProblem);

            end = std::chrono::steady_clock::now();
        }

        auto *lessonplanSchedulingSoultion = new SchedulingSolution(
                bestIndividual,
                lessonplanScoreList->getHardScores(),
                lessonplanScoreList->getSoftScores(),
                lessonplanScoreList->getSummaryHardScores(),
                lessonplanScoreList->getSummarySoftScores(),
                lessonplanScoreList->getLastScoreIndex()
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

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();
        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();

        vector<unsigned short> dataItemIdxsSequence = RandomNumberGenerator::getRandomIdxsSequence(maxDataCount);

        unsigned short classesCount = schedulingProblemProperties->getClassesCount();
        unsigned short subjectsCount = schedulingProblemProperties->getSubjectsCount();

        vector<vector<unsigned short>> classesSubjectsTeachersToAssign = *new vector<vector<unsigned short>>(
                classesCount, vector<unsigned short>(
                        subjectsCount, 0
                )
        );

//        bool changeTeacherLessonAndDay = false; //this->iterationsCountWithSameHardScores[1] > 3;
//        bool changeRoomLessonAndDay = false; //this->iterationsCountWithSameHardScores[2] > 3;

//        std::cout << "b" << std::endl;
//        std::cout << this->iterationsCountWithSameHardScores[1]  << std::endl;
//        std::cout << this->iterationsCountWithSameHardScores[2] << std::endl;
//        std::cout << changeTeacherLessonAndDay << std::endl;
//        std::cout << changeRoomLessonAndDay << std::endl;
//        std::cout << "b" << std::endl;

        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(this->bestIndividual);

        for (unsigned int dataIdxNum = 0; dataIdxNum < maxDataCount; dataIdxNum++) {
            unsigned short dataIdx = dataItemIdxsSequence[dataIdxNum];

            vector<unsigned short> *lessonplanDataItem = &lessonplan[dataIdx];

//            *idx += 1;
            this->reformLessonplanClassSubjectDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                                       lessonplanDataItem);
            lessonplanIndividual->setLessonplan(lessonplan);
            obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);

//            this->hardScores.push_back(obtainedScores[0]);
//            this->softScores.push_back(obtainedScores[1]);
//            this->summaryHardScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[0]));
//            this->summarySoftScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[1]));

//            if (this->summaryHardScores[*idx]  >
//                this->summaryHardScores[*bestIndividualIdx]) {
//                *bestIndividualIdx = *idx;
//                this->bestIndividual = currentIndividual;
//            }

//            *idx += 1;
            this->reformLessonplanTeacherDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                                  lessonplanDataItem);
            lessonplanIndividual->setLessonplan(lessonplan);
            obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);

//            this->hardScores.push_back(obtainedScores[0]);
//            this->softScores.push_back(obtainedScores[1]);
//            this->summaryHardScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[0]));
//            this->summarySoftScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[1]));

//            *idx += 1;
            this->reformLessonplanRoomDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                               lessonplanDataItem);
            lessonplanIndividual->setLessonplan(lessonplan);
            obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);

//            this->hardScores.push_back(obtainedScores[0]);
//            this->softScores.push_back(obtainedScores[1]);
//            this->summaryHardScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[0]));
//            this->summarySoftScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[1]));

//            *idx += 1;
            this->reformLessonplanClassSubjectTeacher(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                                      lessonplanDataItem,
                                                      &classesSubjectsTeachersToAssign);
            lessonplanIndividual->setLessonplan(lessonplan);
            obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);

            lessonplanScoreList->add(obtainedScores);
//            this->individualsHardScores.push_back(obtainedScores[0]);
//            this->individualsSoftScores.push_back(obtainedScores[1]);
//            this->individualsSummaryHardScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[0]));
//            this->individualsSummarySoftScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[1]));
        }

//        lessonplanIndividual->setLessonplan(lessonplan);

        return lessonplanIndividual;
    }


    void SchedulingGreedyAlgorithm::reformLessonplanTeacherDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem) {

        unsigned short teachersCount = schedulingProblemProperties->getTeachersCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short classIdx = (*lessonplanDataItem)[2] - 1;
        unsigned short teacherIdx = (*lessonplanDataItem)[4] - 1;
        unsigned short roomIdx = (*lessonplanDataItem)[5] - 1;

        unsigned short prevAssignedLessonAndDayToTeacher = lessonplanIndividualDescriptor->getAssignedLessonAndDayToTeacher(
                weekDayIdx, lessonIdx, teacherIdx);

        if (prevAssignedLessonAndDayToTeacher > 1) {
            unsigned short teacherIdToChange = RandomNumberGenerator::getRandomNumber(1, teachersCount);
            unsigned short weekDayIdToChange = weekDayIdx + 1;
            unsigned short lessonIdToChange = lessonIdx + 1;

//            std::cout << "change 4" << std::endl;
//            std::cout << reformRandomlySameLessonsData << std::endl;

//            unsigned short randomNumber = RandomNumberGenerator::getRandomNumber(0, 10);
//
//            if (randomNumber == 0) {
//            unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();
//            unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
//
//            weekDayIdToChange = RandomNumberGenerator::getRandomNumber(1, weekDaysCount);
//            lessonIdToChange = RandomNumberGenerator::getRandomNumber(1, lessonsCount);
//
////                std::cout << "change 4 b" << std::endl;
//            }

//            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToClass(weekDayIdx, lessonIdx, classIdx);
            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);
//            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

            (*lessonplanDataItem)[0] = weekDayIdToChange;
            (*lessonplanDataItem)[1] = lessonIdToChange;
            (*lessonplanDataItem)[4] = teacherIdToChange;
            unsigned short weekDayIdxToChange = weekDayIdToChange - 1;
            unsigned short lessonIdxToChange = lessonIdToChange - 1;
            unsigned short teacherIdxToChange = teacherIdToChange - 1;

//            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(weekDayIdxToChange,
//                                                                                lessonIdxToChange,
//                                                                                classIdx);
            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(weekDayIdxToChange, lessonIdxToChange,
                                                                                  teacherIdxToChange);
//            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(weekDayIdxToChange, lessonIdxToChange, roomIdx);
        }
    }

    void SchedulingGreedyAlgorithm::reformLessonplanRoomDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem) {
        unsigned short roomsCount = schedulingProblemProperties->getRoomsCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short classIdx = (*lessonplanDataItem)[2] - 1;
        unsigned short teacherIdx = (*lessonplanDataItem)[4] - 1;
        unsigned short roomIdx = (*lessonplanDataItem)[5] - 1;

        unsigned short prevAssignedLessonAndDayToRoom = lessonplanIndividualDescriptor->getAssignedLessonAndDayToRoom(
                weekDayIdx, lessonIdx, roomIdx);

        if (prevAssignedLessonAndDayToRoom > 1) {
            unsigned short roomIdToChange = RandomNumberGenerator::getRandomNumber(1, roomsCount);
            unsigned short weekDayIdToChange = weekDayIdx + 1;
            unsigned short lessonIdToChange = lessonIdx + 1;

//            if (reformRandomlySameLessonsData) {
//            unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();
//            unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
//
//            weekDayIdToChange = RandomNumberGenerator::getRandomNumber(1, weekDaysCount);
//            lessonIdToChange = RandomNumberGenerator::getRandomNumber(1, lessonsCount);
//
////                std::cout << "change 5" << std::endl;
//            }

//            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToClass(weekDayIdx, lessonIdx, classIdx);
//            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);
            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

            (*lessonplanDataItem)[0] = weekDayIdToChange;
            (*lessonplanDataItem)[1] = lessonIdToChange;
            (*lessonplanDataItem)[5] = roomIdToChange;
            unsigned short weekDayIdxToChange = weekDayIdToChange - 1;
            unsigned short lessonIdxToChange = lessonIdToChange - 1;
            unsigned short roomIdxToChange = roomIdToChange - 1;

//            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(weekDayIdxToChange,
//                                                                                lessonIdxToChange,
//                                                                                classIdx);
//            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(weekDayIdxToChange, lessonIdxToChange,
//                                                                                  teacherIdx);
            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(weekDayIdxToChange, lessonIdxToChange, roomIdxToChange);
        }
    }

    void SchedulingGreedyAlgorithm::reformLessonplanClassSubjectDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem) {
        unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
        unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short classIdx = (*lessonplanDataItem)[2] - 1;
        unsigned short teacherIdx = (*lessonplanDataItem)[4] - 1;
        unsigned short roomIdx = (*lessonplanDataItem)[5] - 1;

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
                vector<unsigned short> weekDaysIdxsSequence = RandomNumberGenerator::getRandomIdxsSequence(
                        weekDaysCount);
                for (unsigned short weekDayIdxNum = 0; weekDayIdxNum < weekDaysCount; weekDayIdxNum++) {
                    unsigned short weekDayIdxToChange = weekDaysIdxsSequence[weekDayIdxNum];
                    unsigned short anotherAssignedLessonAndDayToClass = lessonplanIndividualDescriptor->getAssignedLessonAndDayToClass(
                            weekDayIdxToChange, lessonIdxToChange, classIdx);

                    if (anotherAssignedLessonAndDayToClass <= 0) {

                        lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToClass(weekDayIdx, lessonIdx, classIdx);
                        lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);
                        lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

                        (*lessonplanDataItem)[0] = weekDayIdxToChange + 1;
                        (*lessonplanDataItem)[1] = lessonIdxToChange + 1;

                        lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(weekDayIdxToChange,
                                                                                            lessonIdxToChange,
                                                                                            classIdx);
                        lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(weekDayIdxToChange, lessonIdxToChange,
                                                                                              teacherIdx);
                        lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(weekDayIdxToChange, lessonIdxToChange, roomIdx);
                        return;
                    }
                }
            }
        }
    }

    void SchedulingGreedyAlgorithm::reformLessonplanClassSubjectTeacher(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties, vector<unsigned short> *lessonplanDataItem,
            vector<vector<unsigned short>> *classesSubjectsTeachersToAssign) {
        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short classIdx = (*lessonplanDataItem)[2] - 1;
        unsigned short subjectIdx = (*lessonplanDataItem)[3] - 1;
        unsigned short teacherIdx = (*lessonplanDataItem)[4] - 1;
        unsigned short roomIdx = (*lessonplanDataItem)[5] - 1;

        unsigned short assignedTeachersToClassSubjectWrong = lessonplanIndividualDescriptor->getAssignedTeachersToClassSubjectWrong(
                classIdx, subjectIdx);

        if (assignedTeachersToClassSubjectWrong > 0) {
            unsigned short teacherIdToAssign = (*classesSubjectsTeachersToAssign)[classIdx][subjectIdx];

            if (teacherIdToAssign == 0) {
                (*classesSubjectsTeachersToAssign)[classIdx][subjectIdx] = teacherIdToAssign = SchedulingGreedyAlgorithm::findTeacherForClassSubject(
                        schedulingProblemProperties, subjectIdx + 1);
            }

            unsigned short weekDayIdToChange = weekDayIdx + 1;
            unsigned short lessonIdToChange = lessonIdx + 1;

//            unsigned short weekDaysCount = schedulingProblemProperties->getWeekDaysCount();
//            unsigned short lessonsCount = schedulingProblemProperties->getLessonsCount();
//
//            unsigned short weekDayIdToChange = RandomNumberGenerator::getRandomNumber(1, weekDaysCount);
//            unsigned short lessonIdToChange = RandomNumberGenerator::getRandomNumber(1, lessonsCount);

//            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToClass(weekDayIdx, lessonIdx, classIdx);
            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);
//            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

            (*lessonplanDataItem)[0] = weekDayIdToChange;
            (*lessonplanDataItem)[1] = lessonIdToChange;
            (*lessonplanDataItem)[4] = teacherIdToAssign;
            unsigned short weekDayIdxToChange = weekDayIdToChange - 1;
            unsigned short lessonIdxToChange = lessonIdToChange - 1;
            unsigned short teacherIdxToAssign = teacherIdToAssign - 1;

//            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(weekDayIdxToChange,
//                                                                                lessonIdxToChange,
//                                                                                classIdx);
            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(weekDayIdxToChange, lessonIdxToChange,
                                                                                  teacherIdxToAssign);
//            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(weekDayIdxToChange, lessonIdxToChange, roomIdx);
        }

    }

    unsigned short
    SchedulingGreedyAlgorithm::findTeacherForClassSubject(SchedulingProblemProperties *schedulingProblemProperties,
                                                          unsigned short subjectId) {
        unsigned short teachersCount = schedulingProblemProperties->getTeachersCount();

        vector<unsigned short> teachersIdsSequence = RandomNumberGenerator::getRandomIdsSequence(teachersCount);

        // Iterate through list of teachers
        for (unsigned short teacherIdx = 0; teacherIdx < teachersCount; teacherIdx++) {
            unsigned short teacherId = teachersIdsSequence[teacherIdx];
            vector<unsigned short> teacherSubjects = schedulingProblemProperties->getTeacherSubjects(
                    teacherId - 1);
            auto teacherSubjectsCount = static_cast<unsigned short>(teacherSubjects.size());

            // Iterate through list of teachers subjects
            for (unsigned short subjectIdx2 = 0; subjectIdx2 < teacherSubjectsCount; subjectIdx2++) {
                unsigned short subjectId2 = teacherSubjects[subjectIdx2];

                if (subjectId == subjectId2) {
                    return teacherId;
                }
            }
        }
    }

}
