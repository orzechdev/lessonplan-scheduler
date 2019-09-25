from libcpp.vector cimport vector

cdef extern from "./src/LessonplanScheduler.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanScheduler.hpp" namespace "lessonplans":
    cdef cppclass LessonplanScheduler:
            LessonplanScheduler() except +
            vector[vector[int]] scheduleLessonplan(
                    vector[int] lessons,
                    vector[int] rooms,
                    vector[int] subjects,
                    vector[int] teachers,
                    vector[int] classes
            )
