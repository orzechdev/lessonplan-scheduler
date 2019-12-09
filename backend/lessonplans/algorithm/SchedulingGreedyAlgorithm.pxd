from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from SchedulingProblem cimport SchedulingProblem
from SchedulingSolution cimport SchedulingSolution

cdef extern from "./src/algorithm/greedy/SchedulingGreedyAlgorithm.cpp":
    pass

cdef extern from "./include/algorithm/greedy/SchedulingGreedyAlgorithm.hpp" namespace "lessonplans":
    cdef cppclass SchedulingGreedyAlgorithm:
        SchedulingGreedyAlgorithm(
                int calculations_time_limit_in_seconds
        ) except +
        SchedulingSolution* findBestLessonplan(
                SchedulingProblem* scheduling_problem
        )
