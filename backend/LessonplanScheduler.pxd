cdef extern from "../algorithm/src/LessonplanScheduler.cpp":
    pass

cdef extern from "../algorithm/include/algorithm/LessonplanScheduler.h" namespace "lessonplans":
    cdef cppclass LessonplanScheduler:
            LessonplanScheduler() except +
            LessonplanScheduler(int, int) except +
            int x0, x1
            int scheduleLessonplan()
