#ifndef ALGORITHM_LESSONPLANSCHEDULER_HPP
#define ALGORITHM_LESSONPLANSCHEDULER_HPP

#include <vector>

#include "../../src/LessonplanGenAlgorithm.hpp"

namespace lessonplans {
    class LessonplanScheduler {
        public:
            LessonplanScheduler() {};
            ~LessonplanScheduler() {};
            inline std::vector<std::vector<unsigned short>> scheduleLessonplan(
                unsigned short weekDaysCount,
                unsigned short lessonsCount,
                unsigned short classesCount,
                unsigned short subjectsCount,
                unsigned short teachersCount,
                unsigned short roomsCount,
                std::vector<unsigned short> classesSubjectsRestrictionStatus,
                std::vector<std::vector<unsigned short>> classesSubjects,
                std::vector<unsigned short> teachersSubjectsRestrictionStatus,
                std::vector<std::vector<unsigned short>> teachersSubjects,
                std::vector<unsigned short> roomsSubjectsRestrictionStatus,
                std::vector<std::vector<unsigned short>> roomsSubjects
            );

        private:
             LessonplanGenAlgorithm* lessonplanGenAlgorithm;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULER_HPP
