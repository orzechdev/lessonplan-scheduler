from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from SchedulingProblem cimport SchedulingProblem
from SchedulingSolution cimport SchedulingSolution

cdef extern from "./src/SchedulingRandomSearchAlgorithm.cpp":
    pass

cdef extern from "./include/algorithm/SchedulingRandomSearchAlgorithm.hpp" namespace "lessonplans":
    cdef cppclass SchedulingRandomSearchAlgorithm:
        SchedulingRandomSearchAlgorithm(
                int iterations_count
        ) except +
        SchedulingSolution* findBestLessonplan(
                SchedulingProblem* scheduling_problem
        )
