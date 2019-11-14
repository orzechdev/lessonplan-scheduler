#include <algorithm>
#include "../include/algorithm/SchedulingGreedyAlgorithm.hpp"
#include "RandomNumberGenerator.hpp"

namespace lessonplans {

    SchedulingGreedyAlgorithm::SchedulingGreedyAlgorithm(int iterationsCount){
        this->iterationsCount = iterationsCount;

        this->individuals = *new vector<LessonplanIndividual*>(
                this->iterationsCount
        );
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
        this->individuals[0] = schedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(this->individuals[0]);

        this->individualsHardScores[0] = obtainedScores[0];
        this->individualsSoftScores[0] = obtainedScores[1];

        this->individualsSummaryHardScores[0] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores[0]);
        this->individualsSummarySoftScores[0] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores[1]);

        int bestIndividualIdx = 0;

        for (int i = 1; i < this->iterationsCount; i++) {
            this->individuals[i] = this->alterLessonplan(this->individuals[bestIndividualIdx], schedulingProblem);
            obtainedScores = schedulingProblem->evaluateLessonplan(this->individuals[i]);

            this->individualsHardScores[i] = obtainedScores[0];
            this->individualsSoftScores[i] = obtainedScores[1];

            this->individualsSummaryHardScores[i] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores[0]);
            this->individualsSummarySoftScores[i] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores[1]);

            // Compare scores in greedy way:
            // choose best move in currently occurred situation, i.e. first maximize hard score, and just after then
            // maximize soft score - it might be not be the best chosen path, although it is the greedy chosen path,
            // the best from individual perspective
            if (this->individualsSummaryHardScores[i] == this->individualsSummaryHardScores[bestIndividualIdx]) {
                if (this->individualsSummarySoftScores[i] > this->individualsSummarySoftScores[bestIndividualIdx]) {
                    bestIndividualIdx = i;
                }
            } else if (this->individualsSummaryHardScores[i] > this->individualsSummaryHardScores[bestIndividualIdx]) {
                bestIndividualIdx = i;
            }
        }

        auto* lessonplanSchedulingSoultion = new SchedulingSolution(
                this->iterationsCount,
                this->individuals,
                this->individualsHardScores,
                this->individualsSoftScores,
                this->individualsSummaryHardScores
        );

        return lessonplanSchedulingSoultion;
    }

    LessonplanIndividual *SchedulingGreedyAlgorithm::alterLessonplan(LessonplanIndividual *lessonplanIndividual, SchedulingProblem *schedulingProblem) {
        /*
         * TODO: consider dividing scores during fitness function evaluation into e.g. classes and use those grades
         *  when determining what part of lesson plan should be changed (classIdWithChange and classSubjectIdWithChange)
         *  in order to not just rely on randomness - instead do it as in ideal greedy algorithm (doing best move
         *  in currently occurred situation)
         */

        /*
         * Class is const
         * Subject is const
         *
         * Weekday may change
         * Lesson may change
         * Teacher may change (but for each class and subject pair it must be always the same)
         * Room may change
         */

        unsigned int maxDataCount = lessonplanIndividual->getMaxDataCount();
//        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToClasses = lessonplanIndividual->getAssignedLessonAndDaysToClasses();
//        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToTeachers = lessonplanIndividual->getAssignedLessonAndDaysToTeachers();
//        vector<vector<vector<unsigned short>>> assignedLessonAndDaysToRooms = lessonplanIndividual->getAssignedLessonAndDaysToRooms();

        auto *newLessonplanIndividual = new LessonplanIndividual();

        newLessonplanIndividual->setMaxDataCount(maxDataCount);
        newLessonplanIndividual->setAssignedLessonAndDaysToClasses(lessonplanIndividual->getAssignedLessonAndDaysToClasses());
        newLessonplanIndividual->setAssignedLessonAndDaysToTeachers(lessonplanIndividual->getAssignedLessonAndDaysToTeachers());
        newLessonplanIndividual->setAssignedLessonAndDaysToRooms(lessonplanIndividual->getAssignedLessonAndDaysToRooms());

        vector<vector<unsigned short>> lessonplan = lessonplanIndividual->getLessonplan();

        unsigned short weekDaysCount = schedulingProblem->getSchedulingProblemProperties()->getWeekDaysCount();
        unsigned short lessonsCount = schedulingProblem->getSchedulingProblemProperties()->getLessonsCount();
        unsigned short teacherCount = schedulingProblem->getSchedulingProblemProperties()->getTeachersCount();
        unsigned short roomsCount = schedulingProblem->getSchedulingProblemProperties()->getRoomsCount();
        unsigned short classesCount = schedulingProblem->getSchedulingProblemProperties()->getClassesCount();

        unsigned short classIdWithChange1 = RandomNumberGenerator::getRandomNumber(1, classesCount);
        unsigned short classIdWithChange2 = RandomNumberGenerator::getRandomNumber(1, classesCount);
        unsigned short classIdWithChange3 = RandomNumberGenerator::getRandomNumber(1, classesCount);
        unsigned short classIdWithChange4 = RandomNumberGenerator::getRandomNumber(1, classesCount);

        auto class1SubjectsCount = schedulingProblem->getSchedulingProblemProperties()->getClassSubjectsCount(classIdWithChange1 - 1);
        auto class2SubjectsCount = schedulingProblem->getSchedulingProblemProperties()->getClassSubjectsCount(classIdWithChange2 - 1);
        auto class3SubjectsCount = schedulingProblem->getSchedulingProblemProperties()->getClassSubjectsCount(classIdWithChange3 - 1);
        auto class4SubjectsCount = schedulingProblem->getSchedulingProblemProperties()->getClassSubjectsCount(classIdWithChange4 - 1);

        unsigned short classSubjectIdWithChange1 = RandomNumberGenerator::getRandomNumber(1, class1SubjectsCount);
        unsigned short classSubjectIdWithChange2 = RandomNumberGenerator::getRandomNumber(1, class2SubjectsCount);
        unsigned short classSubjectIdWithChange3 = RandomNumberGenerator::getRandomNumber(1, class3SubjectsCount);
        unsigned short classSubjectIdWithChange4 = RandomNumberGenerator::getRandomNumber(1, class4SubjectsCount);

        unsigned short teacherIdToChange = RandomNumberGenerator::getRandomNumber(1, teacherCount);

        for(unsigned int dataIdx = 0; dataIdx < maxDataCount; dataIdx++) {
            unsigned short classId = lessonplan[dataIdx][2];
            unsigned short subjectId = lessonplan[dataIdx][3];

           if (classId == classIdWithChange1 && subjectId == classSubjectIdWithChange1) {

               unsigned short weekDayId = lessonplan[dataIdx][0];
               unsigned short lessonId = lessonplan[dataIdx][1];
               unsigned short teacherId = lessonplan[dataIdx][4];
               unsigned short roomId = lessonplan[dataIdx][5];

               unsigned short weekDayIdx = weekDayId - 1;
               unsigned short lessonIdx = lessonId - 1;
               unsigned short classIdx = classId - 1;
               unsigned short teacherIdx = teacherId - 1;
               unsigned short roomIdx = roomId - 1;

               newLessonplanIndividual->decreaseAssignedLessonAndDayToClass(weekDayIdx, lessonIdx, classIdx);
               newLessonplanIndividual->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);
               newLessonplanIndividual->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

               // Change assignment count in memory
               unsigned short weekDayIdToChange = RandomNumberGenerator::getRandomNumber(1, weekDaysCount);
               lessonplan[dataIdx][0] = weekDayIdToChange;
               unsigned short weekDayIdxToChange = weekDayIdToChange - 1;

               newLessonplanIndividual->increaseAssignedLessonAndDayToClass(weekDayIdxToChange, lessonIdx, classIdx);
               newLessonplanIndividual->increaseAssignedLessonAndDayToTeacher(weekDayIdxToChange, lessonIdx, teacherIdx);
               newLessonplanIndividual->increaseAssignedLessonAndDayToRoom(weekDayIdxToChange, lessonIdx, roomIdx);

           } else if (classId == classIdWithChange2 && subjectId == classSubjectIdWithChange2) {

               unsigned short weekDayId = lessonplan[dataIdx][0];
               unsigned short lessonId = lessonplan[dataIdx][1];
               unsigned short teacherId = lessonplan[dataIdx][4];
               unsigned short roomId = lessonplan[dataIdx][5];

               unsigned short weekDayIdx = weekDayId - 1;
               unsigned short lessonIdx = lessonId - 1;
               unsigned short classIdx = classId - 1;
               unsigned short teacherIdx = teacherId - 1;
               unsigned short roomIdx = roomId - 1;

               newLessonplanIndividual->decreaseAssignedLessonAndDayToClass(weekDayIdx, lessonIdx, classIdx);
               newLessonplanIndividual->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);
               newLessonplanIndividual->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

               // Change assignment count in memory
               unsigned short lessonIdToChange = RandomNumberGenerator::getRandomNumber(1, lessonsCount);
               lessonplan[dataIdx][1] = lessonIdToChange;
               unsigned short lessonIdxToChange = lessonIdToChange - 1;

               newLessonplanIndividual->increaseAssignedLessonAndDayToClass(weekDayIdx, lessonIdxToChange, classIdx);
               newLessonplanIndividual->increaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdxToChange, teacherIdx);
               newLessonplanIndividual->increaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdxToChange, roomIdx);

           } else if (classId == classIdWithChange3 && subjectId == classSubjectIdWithChange3) {

               unsigned short weekDayId = lessonplan[dataIdx][0];
               unsigned short lessonId = lessonplan[dataIdx][1];
               unsigned short teacherId = lessonplan[dataIdx][4];

               unsigned short weekDayIdx = weekDayId - 1;
               unsigned short lessonIdx = lessonId - 1;
               unsigned short teacherIdx = teacherId - 1;

               newLessonplanIndividual->decreaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdx);

               // Change assignment count in memory
               lessonplan[dataIdx][4] = teacherIdToChange;
               unsigned short teacherIdxToChange = teacherIdToChange - 1;

               newLessonplanIndividual->increaseAssignedLessonAndDayToTeacher(weekDayIdx, lessonIdx, teacherIdxToChange);

           } else if (classId == classIdWithChange4 && subjectId == classSubjectIdWithChange4) {

               unsigned short weekDayId = lessonplan[dataIdx][0];
               unsigned short lessonId = lessonplan[dataIdx][1];
               unsigned short roomId = lessonplan[dataIdx][5];

               unsigned short weekDayIdx = weekDayId - 1;
               unsigned short lessonIdx = lessonId - 1;
               unsigned short roomIdx = roomId - 1;

               newLessonplanIndividual->decreaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdx);

               // Change assignment count in memory
               unsigned short roomIdToChange = RandomNumberGenerator::getRandomNumber(1, roomsCount);
               lessonplan[dataIdx][5] = roomIdToChange;
               unsigned short roomIdxToChange = roomIdToChange - 1;

               newLessonplanIndividual->increaseAssignedLessonAndDayToRoom(weekDayIdx, lessonIdx, roomIdxToChange);

           }
        }

        newLessonplanIndividual->setLessonplan(lessonplan);

        return newLessonplanIndividual;
    }

    int SchedulingGreedyAlgorithm::getSummaryScore(
            vector<int> obtainedScores
    ) {
        int summaryGrade = 0;
        std::for_each(obtainedScores.begin(), obtainedScores.end(), [&] (int grade) {
            summaryGrade += grade;
        });
        return summaryGrade;
    }
}
