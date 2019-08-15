#ifndef ALGORITHM_LESSONPLANSCHEDULER_H
#define ALGORITHM_LESSONPLANSCHEDULER_H

namespace lessonplans {
    class LessonplanScheduler {
        public:
            int x0, x1;
            LessonplanScheduler();
            LessonplanScheduler(int x0, int x1);
            ~LessonplanScheduler();
            int scheduleLessonplan();
    };
}

#endif //ALGORITHM_LESSONPLANSCHEDULER_H
