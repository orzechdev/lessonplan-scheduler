from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from LessonplanSchedulingProblemProperties cimport LessonplanSchedulingProblemProperties

cdef extern from "./src/LessonplanSchedulingProblem.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanSchedulingProblem.hpp" namespace "lessonplans":
    cdef cppclass LessonplanSchedulingProblem:
        LessonplanSchedulingProblem(
                LessonplanSchedulingProblemProperties* lessonplan_scheduling_problem_properties
        ) except +
        short scoresTypes
