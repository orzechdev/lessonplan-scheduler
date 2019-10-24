#ifndef ALGORITHM_LESSONPLANSCHEDULER_HPP
#define ALGORITHM_LESSONPLANSCHEDULER_HPP

#include <vector>

#include "../../src/GenAlgorithm.hpp"

using std::vector;

namespace lessonplans {
    class LessonplanScheduler {
        public:
            LessonplanScheduler() {};
            ~LessonplanScheduler() {};
            inline vector<vector<unsigned short>> scheduleLessonplan(
                unsigned short weekDaysCount,
                unsigned short lessonsCount,
                unsigned short classesCount,
                unsigned short subjectsCount,
                unsigned short teachersCount,
                unsigned short roomsCount,
                vector<unsigned short> classesSubjectsRestrictionStatus,
                vector<vector<unsigned short>> classesSubjects,
                vector<unsigned short> teachersSubjectsRestrictionStatus,
                vector<vector<unsigned short>> teachersSubjects,
                vector<unsigned short> roomsSubjectsRestrictionStatus,
                vector<vector<unsigned short>> roomsSubjects
            );
            inline vector<vector<unsigned short>> getBestLessonplan();
            inline vector<vector<vector<unsigned short>>> getAllLessonplans();

        private:
             GenAlgorithm* genAlgorithm;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULER_HPP
