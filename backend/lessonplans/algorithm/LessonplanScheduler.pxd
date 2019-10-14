from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

cdef extern from "./src/LessonplanScheduler.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanScheduler.hpp" namespace "lessonplans":
    cdef cppclass LessonplanScheduler:
            LessonplanScheduler() except +
            vector[vector[ushort]] scheduleLessonplan(
                    unsigned short week_days_count,
                    unsigned short lessons_count,
                    unsigned short classes_count,
                    unsigned short subjects_count,
                    unsigned short teachers_count,
                    unsigned short rooms_count,
                    vector[ushort] classes_subjects_restriction_status,
                    vector[vector[ushort]] classes_subjects,
                    vector[ushort] teachers_subjects_restriction_status,
                    vector[vector[ushort]] teachers_subjects,
                    vector[ushort] rooms_subjects_restriction_status,
                    vector[vector[ushort]] rooms_subjects
            )
