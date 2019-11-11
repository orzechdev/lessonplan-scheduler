#include <algorithm>
#include "../include/algorithm/SchedulingGreedyAlgorithm.hpp"
#include "RandomNumberGenerator.hpp"

namespace lessonplans {

    SchedulingGreedyAlgorithm::SchedulingGreedyAlgorithm(int iterationsCount){
        this->iterationsCount = iterationsCount;

        this->individuals = *new vector<LessonplanIndividual*>(
                this->iterationsCount
        );
        this->individualsScoresImportant = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::scoresTypesImportant
                )
        );
        this->individualsScoresOptimal = *new vector<vector<int>>(
                this->iterationsCount, vector<int>(
                        SchedulingProblem::scoresTypesOptimal
                )
        );
        this->individualsSummaryScores = *new vector<int>(
                this->iterationsCount
        );
    }

    SchedulingSolution *SchedulingGreedyAlgorithm::findBestLessonplan(SchedulingProblem *schedulingProblem) {
        this->individuals[0] = schedulingProblem->getSampleLessonplan();
        vector<vector<int>> obtainedScores = schedulingProblem->evaluateLessonplan(this->individuals[0]);

        this->individualsScoresImportant[0] = obtainedScores[0];
        this->individualsScoresOptimal[0] = obtainedScores[1];

        this->individualsSummaryScores[0] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores);

        int bestIndividualIdx = 0;

        for (int i = 1; i < this->iterationsCount; i++) {
            this->individuals[i] = this->alterLessonplan(this->individuals[bestIndividualIdx], schedulingProblem);
            obtainedScores = schedulingProblem->evaluateLessonplan(this->individuals[i]);

            this->individualsScoresImportant[i] = obtainedScores[0];
            this->individualsScoresOptimal[i] = obtainedScores[1];

            this->individualsSummaryScores[i] = SchedulingGreedyAlgorithm::getSummaryScore(obtainedScores);

            if (this->individualsSummaryScores[i] > this->individualsSummaryScores[bestIndividualIdx]) {
                bestIndividualIdx = i;
            }
        }

        auto* lessonplanSchedulingSoultion = new SchedulingSolution(
                this->iterationsCount,
                this->individuals,
                this->individualsScoresImportant,
                this->individualsScoresOptimal,
                this->individualsSummaryScores
        );

        return lessonplanSchedulingSoultion;
    }

    LessonplanIndividual *SchedulingGreedyAlgorithm::alterLessonplan(LessonplanIndividual *lessonplanIndividual, SchedulingProblem *schedulingProblem) {
        /*
         * method not yet implemented
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

        vector<unsigned short> class1EachSubjectCount = schedulingProblem->getSchedulingProblemProperties()->getClassSubjectsCount(classIdWithChange1 - 1);
        auto class1SubjectsCount = static_cast<unsigned short>(class1EachSubjectCount.size());
        vector<unsigned short> class2EachSubjectCount = schedulingProblem->getSchedulingProblemProperties()->getClassSubjectsCount(classIdWithChange2 - 1);
        auto class2SubjectsCount = static_cast<unsigned short>(class2EachSubjectCount.size());
        vector<unsigned short> class3EachSubjectCount = schedulingProblem->getSchedulingProblemProperties()->getClassSubjectsCount(classIdWithChange3 - 1);
        auto class3SubjectsCount = static_cast<unsigned short>(class3EachSubjectCount.size());
        vector<unsigned short> class4EachSubjectCount = schedulingProblem->getSchedulingProblemProperties()->getClassSubjectsCount(classIdWithChange4 - 1);
        auto class4SubjectsCount = static_cast<unsigned short>(class4EachSubjectCount.size());

        unsigned short classSubjectIdWithChange1 = RandomNumberGenerator::getRandomNumber(1, class1SubjectsCount);
        unsigned short classSubjectIdWithChange2 = RandomNumberGenerator::getRandomNumber(1, class2SubjectsCount);
        unsigned short classSubjectIdWithChange3 = RandomNumberGenerator::getRandomNumber(1, class3SubjectsCount);
        unsigned short classSubjectIdWithChange4 = RandomNumberGenerator::getRandomNumber(1, class4SubjectsCount);

        unsigned short teacherIdToChange = RandomNumberGenerator::getRandomNumber(1, teacherCount);

        for(unsigned int dataIdx = 0; dataIdx < maxDataCount; dataIdx++) {
            unsigned short classId = lessonplan[dataIdx][2];
            unsigned short subjectId = lessonplan[dataIdx][3];

           if (classId == classIdWithChange1 && subjectId == classSubjectIdWithChange1) {
               unsigned short weekDayIdToChange = RandomNumberGenerator::getRandomNumber(1, weekDaysCount);
               lessonplan[dataIdx][0] = weekDayIdToChange;
           } else if (classId == classIdWithChange2 && subjectId == classSubjectIdWithChange2) {
               unsigned short lessonIdToChange = RandomNumberGenerator::getRandomNumber(1, lessonsCount);
               lessonplan[dataIdx][1] = lessonIdToChange;
           } else if (classId == classIdWithChange3 && subjectId == classSubjectIdWithChange3) {
               lessonplan[dataIdx][4] = teacherIdToChange;
           } else if (classId == classIdWithChange4 && subjectId == classSubjectIdWithChange4) {
               unsigned short roomIdToChange = RandomNumberGenerator::getRandomNumber(1, roomsCount);
               lessonplan[dataIdx][5] = roomIdToChange;
           }
        }

        auto *newLessonplanIndividual = new LessonplanIndividual();

        newLessonplanIndividual->setMaxDataCount(maxDataCount);
        newLessonplanIndividual->setLessonplan(lessonplan);

        return newLessonplanIndividual;
    }

    int SchedulingGreedyAlgorithm::getSummaryScore(
            vector<vector<int>> obtainedScores
    ) {
        int summaryGrade = 0;
        std::for_each(obtainedScores[0].begin(), obtainedScores[0].end(), [&] (int grade) {
            summaryGrade += grade;
        });
        std::for_each(obtainedScores[1].begin(), obtainedScores[1].end(), [&] (int grade) {
            summaryGrade += grade;
        });
        return summaryGrade;
    }
}
