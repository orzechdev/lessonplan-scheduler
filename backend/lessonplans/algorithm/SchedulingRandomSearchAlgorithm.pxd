from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from SchedulingProblem cimport SchedulingProblem
from SchedulingSolution cimport SchedulingSolution

cdef extern from "./src/algorithm/random-search/SchedulingRandomSearchAlgorithm.cpp":
    pass

cdef extern from "./include/algorithm/random-search/SchedulingRandomSearchAlgorithm.hpp" namespace "lessonplans":
    cdef cppclass SchedulingRandomSearchAlgorithm:
        SchedulingRandomSearchAlgorithm(
                int calculations_time_limit_in_seconds
        ) except +
        SchedulingSolution* findBestLessonplan(
                SchedulingProblem* scheduling_problem
        )
