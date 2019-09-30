from libcpp.vector cimport vector
from numpy import ushort

cdef extern from "./src/LessonplanScheduler.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanScheduler.hpp" namespace "lessonplans":
    cdef cppclass LessonplanScheduler:
            LessonplanScheduler() except +
            vector[vector[vector[ushort]]] scheduleLessonplan(
                    unsigned short int day_count,
                    unsigned short int lesson_count,
                    vector[unsigned short int] rooms,
                    vector[unsigned short int] subjects,
                    vector[unsigned short int] teachers,
                    vector[unsigned short int] classes
            )
