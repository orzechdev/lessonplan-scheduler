from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

cdef extern from "./src/LessonplanScheduler.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanScheduler.hpp" namespace "lessonplans":
    cdef cppclass LessonplanScheduler:
            LessonplanScheduler() except +
            vector[vector[ushort]] scheduleLessonplan(
                    vector[vector[vector[vector[ushort]]]] lessons_restrictions_for_individuals,
                    vector[vector[vector[vector[ushort]]]] weekdays_restrictions_for_individuals,
                    vector[vector[vector[vector[ushort]]]] rooms_restrictions_for_individuals,
                    vector[vector[vector[vector[ushort]]]] teachers_restrictions_for_individuals,
                    vector[vector[vector[vector[ushort]]]] classes_restrictions_for_individuals,
                    vector[vector[vector[vector[ushort]]]] subjects_restrictions_for_individuals
            )
