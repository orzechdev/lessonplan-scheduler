#include "LessonplanSchedulingProblem.hpp"

namespace lessonplans {

    LessonplanIndividual* LessonplanSchedulingProblem::getSampleLessonplan(){
        auto* lessonplanIndividual = new LessonplanIndividual();

        lessonplanIndividual->initLessonplan(this->lessonplanData);

        return lessonplanIndividual;
    }

    char LessonplanSchedulingProblem::evaluateLessonplan() {
        return 0;
    }
}