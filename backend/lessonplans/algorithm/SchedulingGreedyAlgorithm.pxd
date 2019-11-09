from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from SchedulingProblem cimport SchedulingProblem
from SchedulingSolution cimport SchedulingSolution

cdef extern from "./src/SchedulingGreedyAlgorithm.cpp":
    pass

cdef extern from "./include/algorithm/SchedulingGreedyAlgorithm.hpp" namespace "lessonplans":
    cdef cppclass SchedulingGreedyAlgorithm:
        SchedulingGreedyAlgorithm(
                int iterations_count
        ) except +
        SchedulingSolution* findBestLessonplan(
                SchedulingProblem* scheduling_problem
        )