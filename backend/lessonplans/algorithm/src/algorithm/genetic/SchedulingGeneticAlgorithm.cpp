#include <algorithm>
#include <chrono>
#include <iostream>
#include "../../../include/algorithm/genetic/SchedulingGeneticAlgorithm.hpp"
#include "../../../include/utils/RandomNumberGenerator.hpp"

/*
 * Note: Some of the methods might be indicated by IDE as unused - it might not be true,
 * because IDE might not detect usages from Cython context.
 */
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
        evaluatePopulation(currentPopulation, schedulingProblem, true);

        int generationIndex = 0;

        while (end - start < timeToWait && lessonplanScoreListPopulation[generationIndex]->getScoreIndexWithZeroSummaryHardAndSoftScore() < 0) {
            std::cout << "process generation " << generationIndex + 1 << " started..." << std::endl;
            std::cout << "crossover..." << std::endl;
            currentPopulation = crossoverPopulation(currentPopulation, schedulingProblem, generationIndex);
            generationIndex++;
            std::cout << "evaluate..." << std::endl;
            evaluatePopulation(currentPopulation, schedulingProblem, true);
            std::cout << "mutate..." << std::endl;
            mutatePopulation(currentPopulation, schedulingProblem, generationIndex);

            std::cout << "process generation " << generationIndex << " finished" << std::endl;

            end = std::chrono::steady_clock::now();
        }

        int bestScoreIndex = lessonplanScoreListPopulation[generationIndex]->getBestScoreIndex();
        bestIndividual = currentPopulation[bestScoreIndex];

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
                    lessonplanScoreList->getBestScoreIndex()
            );
        });

        auto* lessonplanSchedulingEvolutionalSoultion = new SchedulingEvolutionalSolution(
                bestIndividual,
                schedulingSolutions,
                generationIndex
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
        vector<vector<vector<unsigned short>>> nextPopulationLessonplans = *new vector<vector<vector<unsigned short>>>(
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

        // Keep the best individual within next population in place of worst individual
        int currentBestScoreIndex = lessonplanScoreListPopulation[generationIndex]->getBestScoreIndex();
        int currentWorstScoreIndex = lessonplanScoreListPopulation[generationIndex]->getWorstScoreIndex();
        LessonplanIndividualDescriptor* currentBestLessonplanIndividualDescriptor = currentPopulation[currentBestScoreIndex]->getLessonplanIndividualDescriptor();
        LessonplanIndividualDescriptor* currentWorstLessonplanIndividualDescriptor = currentPopulation[currentWorstScoreIndex]->getLessonplanIndividualDescriptor();
        nextPopulationLessonplans[currentWorstScoreIndex] = currentPopulation[currentBestScoreIndex]->getLessonplan();
        currentWorstLessonplanIndividualDescriptor->setAssignedLessonAndDaysToClasses(currentBestLessonplanIndividualDescriptor->getAssignedLessonAndDaysToClasses());
        currentWorstLessonplanIndividualDescriptor->setAssignedLessonAndDaysToTeachers(currentBestLessonplanIndividualDescriptor->getAssignedLessonAndDaysToTeachers());
        currentWorstLessonplanIndividualDescriptor->setAssignedLessonAndDaysToRooms(currentBestLessonplanIndividualDescriptor->getAssignedLessonAndDaysToRooms());

        for (int currentIndividualIdx = 0; currentIndividualIdx < this->populationCount; currentIndividualIdx++) {
            // Keep the best individual within next population in place of worst individual
            if (currentIndividualIdx == currentWorstScoreIndex) {
                continue;
            }

            int populationHardScoreSumAbs = (0 - populationHardScoreSum);
            int currentHardScoreAbs = (0 - summaryHardScores[currentIndividualIdx]);
            int minimumHardScoreNormalizedToSurvive = populationHardScoreSumAbs * (int)(crossoverProbability * 100);
            int currentIndividualHardScoreNormalized = currentHardScoreAbs * 100;

            if (minimumHardScoreNormalizedToSurvive > currentIndividualHardScoreNormalized) {
                std::cout << "individual score hard: " << summaryHardScores[currentIndividualIdx] << ", soft: " << summarySoftScores[currentIndividualIdx] << " survived" << std::endl;
                nextPopulationLessonplans[currentIndividualIdx] = currentPopulation[currentIndividualIdx]->getLessonplan();
                continue;
            }
            std::cout << "individual hard score: " << summaryHardScores[currentIndividualIdx] << ", soft: " << summarySoftScores[currentIndividualIdx] << std::endl;

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

            vector<bool> femaleDataItemPossibleToUse = *new vector<bool>(
                    maxDataCount, true
            );

            LessonplanIndividualDescriptor* lessonplanIndividualDescriptor = currentPopulation[currentIndividualIdx]->getLessonplanIndividualDescriptor();
            for (unsigned int dataItemIdx = 0; dataItemIdx < maxDataCount; dataItemIdx++) {
                vector<unsigned short> currentDataItem = currentLessonplan[dataItemIdx];
                vector<unsigned short> maleDataItem = maleLessonplan[dataItemIdx];

                bool dataItemForMale = false;
                for (unsigned short classToTakeIdx = 0; classToTakeIdx < halfClassesCount; classToTakeIdx++) {
                    if (classesForMaleLessonplan[classToTakeIdx] == maleDataItem[2] - 1) {
                        dataItemForMale = true;
                        break;
                    }
                }

                lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToClass(currentDataItem[0] - 1, currentDataItem[1] - 1, currentDataItem[2] - 1);
                lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(currentDataItem[0] - 1, currentDataItem[1] - 1, currentDataItem[4] - 1);
                lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(currentDataItem[0] - 1, currentDataItem[1] - 1, currentDataItem[5] - 1);

                if (dataItemForMale) {
                    childLessonplan[dataItemIdx] = maleDataItem;
                    lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(maleDataItem[0] - 1, maleDataItem[1] - 1, maleDataItem[2] - 1);
                    lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(maleDataItem[0] - 1, maleDataItem[1] - 1, maleDataItem[4] - 1);
                    lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(maleDataItem[0] - 1, maleDataItem[1] - 1, maleDataItem[5] - 1);
                } else {
                    for (unsigned int femaleDataItemIdx = 0; femaleDataItemIdx < maxDataCount; femaleDataItemIdx++) {
                        vector<unsigned short> femaleDataItem = femaleLessonplan[femaleDataItemIdx];

                        if (femaleDataItemPossibleToUse[femaleDataItemIdx]) {
                            bool dataItemNotForFemale = false;

                            for (unsigned short classToTakeIdx = 0; classToTakeIdx < halfClassesCount; classToTakeIdx++) {
                                if (classesForMaleLessonplan[classToTakeIdx] == femaleDataItem[2] - 1) {
                                    dataItemNotForFemale = true;
                                    femaleDataItemPossibleToUse[femaleDataItemIdx] = false;
                                    break;
                                }
                            }

                            if (!dataItemNotForFemale) {
                                childLessonplan[dataItemIdx] = femaleDataItem;
                                lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToClass(femaleDataItem[0] - 1, femaleDataItem[1] - 1, femaleDataItem[2] - 1);
                                lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(femaleDataItem[0] - 1, femaleDataItem[1] - 1, femaleDataItem[4] - 1);
                                lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToRoom(femaleDataItem[0] - 1, femaleDataItem[1] - 1, femaleDataItem[5] - 1);
                                femaleDataItemPossibleToUse[femaleDataItemIdx] = false;
                                break;
                            }
                        }
                    }
                }
            }

            nextPopulationLessonplans[currentIndividualIdx] = childLessonplan;
        }

        for (int currentIndividualIdx = 0; currentIndividualIdx < this->populationCount; currentIndividualIdx++) {
            currentPopulation[currentIndividualIdx]->setLessonplan(nextPopulationLessonplans[currentIndividualIdx]);
        }

        return currentPopulation;
    }

    void SchedulingGeneticAlgorithm::mutatePopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem, int generationIndex){
        for (int j = 0; j < 1; j++) {
            for (int i = 0; i < populationCount; i++) {
                reformLessonplan(currentPopulation[i], schedulingProblem, generationIndex);
            }

            std::cout << "evaluate..." << std::endl;
            evaluatePopulation(currentPopulation, schedulingProblem, false);
        }
    }

    void SchedulingGeneticAlgorithm::evaluatePopulation(vector<LessonplanIndividual *> currentPopulation, SchedulingProblem *schedulingProblem, bool addScoreForNewGeneration){
        auto* lessonplanScoreList = new LessonplanScoreList();

        for (int i = 0; i < populationCount; i++) {
            vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(currentPopulation[i]);
            lessonplanScoreList->add(obtainedScores);
        }

        if (addScoreForNewGeneration) {
            lessonplanScoreListPopulation.push_back(lessonplanScoreList);
        } else {
            lessonplanScoreListPopulation.back() = lessonplanScoreList;
        }
    }

    int SchedulingGeneticAlgorithm::select(int generationIndex, int populationHardScoreSum, int populationSoftScoreSum, bool includeSoftScore, int excludeIndex) {
        vector<int> summaryHardScores = lessonplanScoreListPopulation[generationIndex]->getSummaryHardScores();
        vector<int> summarySoftScores = lessonplanScoreListPopulation[generationIndex]->getSummarySoftScores();

        int totalWeight = 0;
        totalWeight -= populationHardScoreSum;
        if (includeSoftScore) {
            totalWeight -= populationSoftScoreSum;
        }
        int randomWeight = totalWeight > 1 ? RandomNumberGenerator::getRandomNumber(0, totalWeight - 1) : totalWeight;

        int index = 0;
        for (index = 0; index < this->populationCount; index++) {
            int individualWeight = totalWeight - summaryHardScores[index];
            if (includeSoftScore) {
                individualWeight += totalWeight - summarySoftScores[index];
            }

            if(randomWeight < individualWeight && index != excludeIndex) {
                return index;
            }
            randomWeight -= individualWeight;
        }
        return RandomNumberGenerator::getRandomNumber(0, this->populationCount - 1);
    }

    LessonplanIndividual *SchedulingGeneticAlgorithm::reformLessonplan(LessonplanIndividual *lessonplanIndividual,
                                                                      SchedulingProblem *schedulingProblem,
                                                                      int generationIndex) {
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

        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);
        for (unsigned int dataIdxNum = 0; dataIdxNum < maxDataCount; dataIdxNum++) {
            unsigned short dataIdx = dataItemIdxsSequence[dataIdxNum];

            vector<unsigned short> *lessonplanDataItem = &lessonplan[dataIdx];

            this->reformLessonplanClassSubjectDataItem(lessonplanIndividualDescriptor,
                                                       schedulingProblemProperties,
                                                       lessonplanDataItem);
            lessonplanIndividual->setLessonplan(lessonplan);
            obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);

            this->reformLessonplanTeacherDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                                  lessonplanDataItem);
            lessonplanIndividual->setLessonplan(lessonplan);
            obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);

            this->reformLessonplanRoomDataItem(lessonplanIndividualDescriptor, schedulingProblemProperties,
                                               lessonplanDataItem);
            lessonplanIndividual->setLessonplan(lessonplan);
            obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);

            this->reformLessonplanClassSubjectTeacher(lessonplanIndividualDescriptor,
                                                      schedulingProblemProperties,
                                                      lessonplanDataItem,
                                                      &classesSubjectsTeachersToAssign);
            lessonplanIndividual->setLessonplan(lessonplan);
            obtainedScores = schedulingProblem->evaluateLessonplan(lessonplanIndividual);
        }

        return lessonplanIndividual;
    }


    void SchedulingGeneticAlgorithm::reformLessonplanTeacherDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem) {

        unsigned short teachersCount = schedulingProblemProperties->getTeachersCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short teacherIdx = (*lessonplanDataItem)[4] - 1;

        unsigned short prevAssignedLessonAndDayToTeacher = lessonplanIndividualDescriptor->getAssignedLessonAndDayToTeacher(
                weekDayIdx, lessonIdx, teacherIdx);

        if (prevAssignedLessonAndDayToTeacher > 1) {
            unsigned short teacherIdToChange = RandomNumberGenerator::getRandomNumber(1, teachersCount);
            unsigned short weekDayIdToChange = weekDayIdx + 1;
            unsigned short lessonIdToChange = lessonIdx + 1;

            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);

            (*lessonplanDataItem)[0] = weekDayIdToChange;
            (*lessonplanDataItem)[1] = lessonIdToChange;
            (*lessonplanDataItem)[4] = teacherIdToChange;
            unsigned short weekDayIdxToChange = weekDayIdToChange - 1;
            unsigned short lessonIdxToChange = lessonIdToChange - 1;
            unsigned short teacherIdxToChange = teacherIdToChange - 1;

            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(weekDayIdxToChange, lessonIdxToChange,
                                                                                  teacherIdxToChange);
        }
    }

    void SchedulingGeneticAlgorithm::reformLessonplanRoomDataItem(
            LessonplanIndividualDescriptor *lessonplanIndividualDescriptor,
            SchedulingProblemProperties *schedulingProblemProperties,
            vector<unsigned short> *lessonplanDataItem) {
        unsigned short roomsCount = schedulingProblemProperties->getRoomsCount();

        unsigned short weekDayIdx = (*lessonplanDataItem)[0] - 1;
        unsigned short lessonIdx = (*lessonplanDataItem)[1] - 1;
        unsigned short roomIdx = (*lessonplanDataItem)[5] - 1;

        unsigned short prevAssignedLessonAndDayToRoom = lessonplanIndividualDescriptor->getAssignedLessonAndDayToRoom(
                weekDayIdx, lessonIdx, roomIdx);

        if (prevAssignedLessonAndDayToRoom > 1) {
            unsigned short roomIdToChange = RandomNumberGenerator::getRandomNumber(1, roomsCount);
            unsigned short weekDayIdToChange = weekDayIdx + 1;
            unsigned short lessonIdToChange = lessonIdx + 1;

            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

            (*lessonplanDataItem)[0] = weekDayIdToChange;
            (*lessonplanDataItem)[1] = lessonIdToChange;
            (*lessonplanDataItem)[5] = roomIdToChange;
            unsigned short weekDayIdxToChange = weekDayIdToChange - 1;
            unsigned short lessonIdxToChange = lessonIdToChange - 1;
            unsigned short roomIdxToChange = roomIdToChange - 1;

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

        bool softReformShouldOccur = true;
        if ((unsigned short)(mutationProbability * 100) < RandomNumberGenerator::getRandomNumber(1, 100)) {
            softReformShouldOccur = false;
        }

        unsigned short classStartLessonsDifferenceCountAverage = lessonplanIndividualDescriptor->getClassesStartLessonsDifferenceCountAverage()[classIdx];
        unsigned short classLessonsCountDifferenceBetweenDaysAverage = lessonplanIndividualDescriptor->getClassesLessonsCountAverageDifferenceBetweenDays()[classIdx];
        unsigned short classFreePeriodsExistenceBetweenLessonsCount = lessonplanIndividualDescriptor->getClassesFreePeriodsExistenceBetweenLessonsCount()[classIdx];

        if (prevAssignedLessonAndDayToClass > 1 ||
            (softReformShouldOccur && (
            classStartLessonsDifferenceCountAverage > 1 ||
            classLessonsCountDifferenceBetweenDaysAverage > 1 ||
            classFreePeriodsExistenceBetweenLessonsCount > 0))) {
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

            lessonplanIndividualDescriptor->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);

            (*lessonplanDataItem)[0] = weekDayIdToChange;
            (*lessonplanDataItem)[1] = lessonIdToChange;
            (*lessonplanDataItem)[4] = teacherIdToAssign;
            unsigned short weekDayIdxToChange = weekDayIdToChange - 1;
            unsigned short lessonIdxToChange = lessonIdToChange - 1;
            unsigned short teacherIdxToAssign = teacherIdToAssign - 1;

            lessonplanIndividualDescriptor->increaseAssignedLessonAndDayToTeacher(weekDayIdxToChange, lessonIdxToChange,
                                                                                  teacherIdxToAssign);
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
