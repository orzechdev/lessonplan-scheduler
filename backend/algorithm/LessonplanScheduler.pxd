from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

cdef extern from "./src/LessonplanScheduler.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanScheduler.hpp" namespace "lessonplans":
    cdef cppclass LessonplanScheduler:
            LessonplanScheduler() except +
            vector[vector[vector[vector[ushort]]]] scheduleLessonplan(
                    unsigned short int class_count,
                    unsigned short int day_count,
                    unsigned short int lesson_count,
                    vector[unsigned short int] rooms,
                    vector[unsigned short int] teachers,
                    vector[vector[vector[ushort]]] classes_subjects_with_classes_subjects_hours,
                    vector[bool] rooms_exclusive_assignments,
                    vector[vector[ushort]] subjects_rooms,
                    vector[vector[ushort]] teachers_subjects
            )
