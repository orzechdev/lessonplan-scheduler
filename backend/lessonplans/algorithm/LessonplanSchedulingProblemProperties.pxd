from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

cdef extern from "./src/LessonplanSchedulingProblemProperties.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanSchedulingProblemProperties.hpp" namespace "lessonplans":
    cdef cppclass LessonplanSchedulingProblemProperties:
        LessonplanSchedulingProblemProperties(
                unsigned short week_days_count,
                unsigned short lessons_count,
                unsigned short classes_count,
                unsigned short subjects_count,
                unsigned short teachers_count,
                unsigned short rooms_count,
                vector[vector[ushort]] classes_subjects,
                vector[vector[ushort]] teachers_subjects,
                vector[vector[ushort]] rooms_subjects,
                vector[vector[ushort]] classes_subjects_count
        ) except +
