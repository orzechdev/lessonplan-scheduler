#ifndef ALGORITHM_LESSONPLANSCHEDULER_H
#define ALGORITHM_LESSONPLANSCHEDULER_H

#include <vector>

#include "../../src/LessonplanGenAlgorithm.h"

namespace lessonplans {
    class LessonplanScheduler {
        public:
            LessonplanScheduler();
            ~LessonplanScheduler();
            std::vector<std::vector<int>> scheduleLessonplan(
                    std::vector<int> lessons,
                    std::vector<int> rooms,
                    std::vector<int> subjects,
                    std::vector<int> teachers,
                    std::vector<int> classes
            );

        private:
             LessonplanGenAlgorithm* lessonplanGenAlgorithm;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULER_H
