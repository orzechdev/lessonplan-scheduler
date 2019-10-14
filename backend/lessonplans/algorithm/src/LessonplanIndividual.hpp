#ifndef ALGORITHM_LESSONPLANINDIVIDUAL_H
#define ALGORITHM_LESSONPLANINDIVIDUAL_H

#include <vector>

#include "Individual.hpp"

namespace lessonplans {
    class LessonplanIndividual : public Individual {
    public:
        LessonplanIndividual() : Individual() {}
        bool init() override;
        std::vector<unsigned short> determinePossibleWeekDayAndLesson();
    };
}

#endif //ALGORITHM_LESSONPLANINDIVIDUAL_H
