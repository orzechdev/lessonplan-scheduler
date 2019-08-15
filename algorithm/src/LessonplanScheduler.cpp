#include "../include/algorithm/LessonplanScheduler.h"

namespace lessonplans {
    LessonplanScheduler::LessonplanScheduler() {}

    LessonplanScheduler::LessonplanScheduler(int x0, int x1) {
        this->x0 = x0;
        this->x1 = x1;
    }

    LessonplanScheduler::~LessonplanScheduler() {}

    int LessonplanScheduler::scheduleLessonplan() {
        return this->x0 + this->x1;
    }
}
