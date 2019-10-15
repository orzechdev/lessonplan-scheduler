#ifndef ALGORITHM_LESSONPLANINDIVIDUAL_H
#define ALGORITHM_LESSONPLANINDIVIDUAL_H

#include <vector>

#include "Individual.hpp"

namespace lessonplans {
    class LessonplanIndividual : public Individual {
    public:
        LessonplanIndividual() : Individual() {}
        std::vector<std::vector<unsigned short>> initLessonplan(
                unsigned short weekDaysCount,
                unsigned short lessonsCount,
                unsigned short classesCount,
                unsigned short subjectsCount,
                unsigned short teachersCount,
                unsigned short roomsCount,
                std::vector<std::vector<unsigned short>> classesSubjects,
                std::vector<std::vector<unsigned short>> teachersSubjects,
                std::vector<unsigned short> roomsSubjectsRestrictionStatus,
                std::vector<std::vector<unsigned short>> roomsSubjects
        );
        std::vector<std::vector<unsigned short>> getIndividual();

    private:
        static const short dataTypes = 6;
        unsigned int maxDataCount;
        std::vector<std::vector<unsigned short>> individual;
        std::vector<std::vector<std::vector<unsigned short>>> assignedLessonAndDaysToClasses;
        std::vector<std::vector<std::vector<unsigned short>>> assignedLessonAndDaysToTeachers;
        std::vector<std::vector<std::vector<unsigned short>>> assignedLessonAndDaysToRooms;
        std::vector<unsigned short> determinePossibleWeekDayAndLesson(
                unsigned short weekDaysCount,
                unsigned short lessonsCount,
                unsigned short classIdx,
                unsigned short teacherIdx,
                unsigned short roomIdx
        );
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUAL_H
