#ifndef ALGORITHM_LESSONPLANSCHEDULER_HPP
#define ALGORITHM_LESSONPLANSCHEDULER_HPP

#include <vector>

#include "../../src/LessonplanGenAlgorithm.hpp"

namespace lessonplans {
    class LessonplanScheduler {
        public:
            LessonplanScheduler() {};
            ~LessonplanScheduler() {};
            inline std::vector<std::vector<int>> scheduleLessonplan(
                    unsigned short int dayCount,
                    unsigned short int lessonCount,
                    std::vector<int> rooms,
                    std::vector<int> subjects,
                    std::vector<int> teachers,
                    std::vector<int> classes
            );

        private:
             LessonplanGenAlgorithm* lessonplanGenAlgorithm;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULER_HPP
