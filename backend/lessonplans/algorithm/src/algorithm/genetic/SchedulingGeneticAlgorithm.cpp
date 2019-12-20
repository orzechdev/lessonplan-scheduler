#include <algorithm>
#include <chrono>
#include <iostream>
#include "../../../include/algorithm/genetic/SchedulingGeneticAlgorithm.hpp"
#include "../../../include/lessonplan/LessonplanScoreList.hpp"
#include "../../../include/utils/RandomNumberGenerator.hpp"

namespace lessonplans {

    SchedulingGeneticAlgorithm::SchedulingGeneticAlgorithm(int calculationsTimeLimitInSeconds, int populationCount,
                                                           float crossoverProbability, float mutationProbability) {
        this->calculationsTimeLimitInSeconds = calculationsTimeLimitInSeconds;
        this->populationCount = populationCount;
        this->crossoverProbability = crossoverProbability;
        this->mutationProbability = mutationProbability;

        this->lessonplanScoreListPopulation = *new vector<LessonplanScoreList*>(
                0
        );
    }

    SchedulingEvolutionalSolution *SchedulingGeneticAlgorithm::findBestLessonplan(SchedulingProblem *schedulingProblem) {
        auto start = std::chrono::steady_clock::now();
        auto end = start;
        auto timeToWait = std::chrono::seconds(calculationsTimeLimitInSeconds);

        vector<LessonplanIndividual *> currentPopulation = initializePopulation(schedulingProblem);
        evaluatePopulation(currentPopulation, schedulingProblem);

//        this->select();

        int generationIndex = 0;

        while (end - start < timeToWait && lessonplanScoreListPopulation[generationIndex]->getScoreIndexWithZeroSummaryHardAndSoftScore() < 0) {
            std::cout << "log 0 0 1" << std::endl;
            currentPopulation = crossoverPopulation(currentPopulation, schedulingProblem, generationIndex);
            std::cout << "log 0 0 2" << std::endl;
            mutatePopulation(currentPopulation, schedulingProblem);
            std::cout << "log 0 0 3" << std::endl;

            evaluatePopulation(currentPopulation, schedulingProblem);
            std::cout << "log 0 0 4" << std::endl;

            generationIndex++;

            end = std::chrono::steady_clock::now();
        }

        int scoreIndexWithZeroSummaryHardAndSoftScore = lessonplanScoreListPopulation[generationIndex]->getScoreIndexWithZeroSummaryHardAndSoftScore();
        if (scoreIndexWithZeroSummaryHardAndSoftScore >= 0) {
            bestIndividual = currentPopulation[scoreIndexWithZeroSummaryHardAndSoftScore];
        } else {
            bestIndividual = currentPopulation.back();
        }

        vector<SchedulingSolution *> schedulingSolutions;
        std::transform(
                lessonplanScoreListPopulation.begin(),
                lessonplanScoreListPopulation.end(),
                std::back_inserter(schedulingSolutions),
                [](LessonplanScoreList* lessonplanScoreList
        ) {
            return new SchedulingSolution(
                    nullptr,
                    lessonplanScoreList->getHardScores(),
                    lessonplanScoreList->getSoftScores(),
                    lessonplanScoreList->getSummaryHardScores(),
                    lessonplanScoreList->getSummarySoftScores(),
                    lessonplanScoreList->getLastScoreIndex()
            );
        });

        auto* lessonplanSchedulingEvolutionalSoultion = new SchedulingEvolutionalSolution(
                bestIndividual,
                schedulingSolutions,
                0
        );

        return lessonplanSchedulingEvolutionalSoultion;
    }

    vector<LessonplanIndividual *> SchedulingGeneticAlgorithm::initializePopulation(SchedulingProblem *schedulingProblem) {
        vector<LessonplanIndividual *> population = *new vector<LessonplanIndividual*>(
                this->populationCount
        );

        for (int i = 0; i < this->populationCount; i++) {
            population[i] = schedulingProblem->getSampleLessonplan();
        }

        return population;
    }

    vector<LessonplanIndividual *> SchedulingGeneticAlgorithm::crossoverPopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem, int generationIndex){
        std::cout << "log 1 0 1" << std::endl;
        vector<vector<vector<unsigned short>>> lessonplans = *new vector<vector<vector<unsigned short>>>(
                this->populationCount
        );
        vector<int> summaryHardScores = lessonplanScoreListPopulation[generationIndex]->getSummaryHardScores();
        vector<int> summarySoftScores = lessonplanScoreListPopulation[generationIndex]->getSummarySoftScores();
        int populationHardScoreSum = 0;
        int populationSoftScoreSum = 0;
        std::for_each(
                summaryHardScores.begin(),
                summaryHardScores.end(), [&](int score) {
                    populationHardScoreSum += score;
                }
        );
        std::for_each(
                summarySoftScores.begin(),
                summarySoftScores.end(), [&](int score) {
                    populationSoftScoreSum += score;
                }
        );
        std::cout << "log 1 0 2" << std::endl;

        for (int currentIndividualIdx = 0; currentIndividualIdx < this->populationCount; currentIndividualIdx++) {
            std::cout << "log 1 0 3" << std::endl;
            int selectedMaleIndividualIndex = SchedulingGeneticAlgorithm::select(
                    generationIndex, populationHardScoreSum, populationSoftScoreSum, false, -1
            );
            int selectedFemaleIndividualIndex = SchedulingGeneticAlgorithm::select(
                    generationIndex, populationHardScoreSum, populationSoftScoreSum, true, selectedMaleIndividualIndex
            );

            vector<vector<unsigned short>> currentLessonplan = currentPopulation[currentIndividualIdx]->getLessonplan();
            vector<vector<unsigned short>> maleLessonplan = currentPopulation[selectedMaleIndividualIndex]->getLessonplan();
            vector<vector<unsigned short>> femaleLessonplan = currentPopulation[selectedFemaleIndividualIndex]->getLessonplan();

            unsigned short classesCount = schedulingProblem->getSchedulingProblemProperties()->getClassesCount();
            auto halfClassesCount = (unsigned short)(classesCount / 2);
            vector<unsigned short> classesForMaleLessonplan = *new vector<unsigned short>(0);

            for (unsigned short classToTakeIdx = 0; classToTakeIdx < halfClassesCount; classToTakeIdx++) {
                classesForMaleLessonplan.push_back(RandomNumberGenerator::getRandomNumber(0, classesCount - 1));
            }

            unsigned int maxDataCount = currentPopulation[selectedMaleIndividualIndex]->getMaxDataCount();
            vector<vector<unsigned short>> childLessonplan = *new vector<vector<unsigned short>>(
                    maxDataCount, vector<unsigned short>(
                            LessonplanIndividual::dataTypes
                    )
            );

            LessonplanIndividualDescriptor* lessonplanIndividualDescriptor = currentPopulation[currentIndividualIdx]->getLessonplanIndividualDescriptor();
            std::cout << "log 1 0 4" << std::endl;
            for (unsigned int dataItemIdx = 0; dataItemIdx < maxDataCount; dataItemIdx++) {
                vector<unsigned short> currentDataItem = currentLessonplan[dataItemIdx];
                vector<unsigned short> maleDataItem = maleLessonplan[dataItemIdx];
                vector<unsigned short> femaleDataItem = femaleLessonplan[dataItemIdx];

                bool dataItemForMale = false;
                for (unsigned short classToTakeIdx = 0; classToTakeIdx < halfClassesCount; classToTakeIdx++) {
                    if (classesForMaleLessonplan[classToTakeIdx] == maleDataItem[2] - 1) {
                        dataItemForMale = true;
                        break;
                    }
                }

                if (dataItemForMale) {
                    lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToClass(currentDataItem[0] - 1, currentDataItem[1] - 1, currentDataItem[2] - 1);
                    lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(currentDataItem[0] - 1, currentDataItem[1] - 1, currentDataItem[4] - 1);
                    lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(currentDataItem[0] - 1, currentDataItem[1] - 1, currentDataItem[5] - 1);
                    childLessonplan[dataItemIdx] = maleDataItem;
                    lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(maleDataItem[0] - 1, maleDataItem[1] - 1, maleDataItem[2] - 1);
                    lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(maleDataItem[0] - 1, maleDataItem[1] - 1, maleDataItem[4] - 1);
                    lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(maleDataItem[0] - 1, maleDataItem[1] - 1, maleDataItem[5] - 1);
                } else {
                    lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToClass(currentDataItem[0] - 1, currentDataItem[1] - 1, currentDataItem[2] - 1);
                    lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(currentDataItem[0] - 1, currentDataItem[1] - 1, currentDataItem[4] - 1);
                    lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(currentDataItem[0] - 1, currentDataItem[1] - 1, currentDataItem[5] - 1);
                    childLessonplan[dataItemIdx] = femaleDataItem;
                    lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(femaleDataItem[0] - 1, femaleDataItem[1] - 1, femaleDataItem[2] - 1);
                    lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(femaleDataItem[0] - 1, femaleDataItem[1] - 1, femaleDataItem[4] - 1);
                    lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(femaleDataItem[0] - 1, femaleDataItem[1] - 1, femaleDataItem[5] - 1);
                }
            }

            currentPopulation[currentIndividualIdx]->setLessonplan(childLessonplan);
        }
        std::cout << "log 1 0 5" << std::endl;

        return currentPopulation;
    }

    void SchedulingGeneticAlgorithm::mutatePopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem){
        std::cout << "log 0 1" << std::endl;
        for (int i = 0; i < populationCount; i++) {
            std::cout << "log 0 2" << std::endl;
            reformLessonplan(currentPopulation[i], schedulingProblem);
            std::cout << "log 0 3" << std::endl;
        }
    }

    void SchedulingGeneticAlgorithm::evaluatePopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem){
        auto* lessonplanScoreList = new LessonplanScoreList();

        for (int i = 0; i < populationCount; i++) {
            vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(currentPopulation[i]);
            lessonplanScoreList->add(obtainedScores);
        }

        lessonplanScoreListPopulation.push_back(lessonplanScoreList);
    }

    int SchedulingGeneticAlgorithm::select(int generationIndex, int populationHardScoreSum, int populationSoftScoreSum, bool includeSoftScore, int excludeIndex) {
        int maxScore = 0;
        maxScore -= populationHardScoreSum;
        if (includeSoftScore) {
            maxScore -= populationSoftScoreSum;
        }
        int pick = RandomNumberGenerator::getRandomNumber(0, maxScore);
        int offset = 0;

        for (int index = 0; index < this->populationCount; index++) {
            if (index == excludeIndex) {
                continue;
            }
            offset -= lessonplanScoreListPopulation[generationIndex]->getSummaryHardScores()[index];
            if (includeSoftScore) {
                offset -= lessonplanScoreListPopulation[generationIndex]->getSummarySoftScores()[index];
            }
            if (pick < offset) {
                return index;
            }
        }
    }

    LessonplanIndividual *SchedulingGeneticAlgorithm::reformLessonplan(LessonplanIndividual *lessonplanIndividual,
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
        std::cout << "log 1" << std::endl;

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

        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);
        std::cout << "log 2" << std::endl;
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

            // !!!!!!!!!!!!!!!
            // !!!!!!!!!!!!!!!
            // !!!!!!!!!!!!!!!
//            lessonplanScoreList->add(obtainedScores);
            // !!!!!!!!!!!!!!!
            // !!!!!!!!!!!!!!!
            // !!!!!!!!!!!!!!!
//            this->individualsHardScores.push_back(obtainedScores[0]);
//            this->individualsSoftScores.push_back(obtainedScores[1]);
//            this->individualsSummaryHardScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[0]));
//            this->individualsSummarySoftScores.push_back(SchedulingProblem::calculateSummaryScore(obtainedScores[1]));
        }
        std::cout << "log 3" << std::endl;
//        lessonplanIndividual->setLessonplan(lessonplan);

        return lessonplanIndividual;
    }


    void SchedulingGeneticAlgorithm::reformLessonplanTeacherDataItem(
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

    void SchedulingGeneticAlgorithm::reformLessonplanRoomDataItem(
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

    void SchedulingGeneticAlgorithm::reformLessonplanClassSubjectDataItem(
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

    void SchedulingGeneticAlgorithm::reformLessonplanClassSubjectTeacher(
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
                (*classesSubjectsTeachersToAssign)[classIdx][subjectIdx] = teacherIdToAssign = SchedulingGeneticAlgorithm::findTeacherForClassSubject(
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
    SchedulingGeneticAlgorithm::findTeacherForClassSubject(SchedulingProblemProperties *schedulingProblemProperties,
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
