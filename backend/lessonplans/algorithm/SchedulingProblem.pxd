from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from SchedulingProblemProperties cimport SchedulingProblemProperties

cdef extern from "./src/algorithm/SchedulingProblem.cpp":
    pass

cdef extern from "./include/algorithm/SchedulingProblem.hpp" namespace "lessonplans":
    cdef cppclass SchedulingProblem:
        SchedulingProblem(
                SchedulingProblemProperties* scheduling_problem_properties
        ) except +
        short scoresTypes
