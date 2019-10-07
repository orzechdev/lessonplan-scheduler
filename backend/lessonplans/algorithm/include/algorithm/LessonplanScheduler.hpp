#ifndef ALGORITHM_LESSONPLANSCHEDULER_HPP
#define ALGORITHM_LESSONPLANSCHEDULER_HPP

#include <vector>

#include "../../src/LessonplanGenAlgorithm.hpp"

namespace lessonplans {
    class LessonplanScheduler {
        public:
            LessonplanScheduler() {};
            ~LessonplanScheduler() {};
            inline std::vector<std::vector<std::vector<std::vector<unsigned short>>>> scheduleLessonplan(
                    unsigned short classCount,
                    unsigned short dayCount,
                    unsigned short lessonCount,
                    std::vector<unsigned short> rooms,
                    std::vector<unsigned short> teachers,
                    std::vector<std::vector<std::vector<unsigned short>>> classesSubjectsIdsWithClassesSubjectsHours,
                    std::vector<bool> roomsExclusiveAssignments,
                    std::vector<std::vector<unsigned short>> subjectsRooms,
                    std::vector<std::vector<unsigned short>> teachersSubjects
            );

        private:
             LessonplanGenAlgorithm* lessonplanGenAlgorithm;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULER_HPP
