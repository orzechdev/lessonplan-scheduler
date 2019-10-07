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
                std::vector<std::vector<std::vector<std::vector<unsigned short>>>> lessonsRestrictionsForIndividuals,
                std::vector<std::vector<std::vector<std::vector<unsigned short>>>> weekDaysRestrictionsForIndividuals,
                std::vector<std::vector<std::vector<std::vector<unsigned short>>>> roomsRestrictionsForIndividuals,
                std::vector<std::vector<std::vector<std::vector<unsigned short>>>> teachersRestrictionsForIndividuals,
                std::vector<std::vector<std::vector<std::vector<unsigned short>>>> classesRestrictionsForIndividuals,
                std::vector<std::vector<std::vector<std::vector<unsigned short>>>> subjectsRestrictionsForIndividuals
            );

        private:
             LessonplanGenAlgorithm* lessonplanGenAlgorithm;
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULER_HPP
