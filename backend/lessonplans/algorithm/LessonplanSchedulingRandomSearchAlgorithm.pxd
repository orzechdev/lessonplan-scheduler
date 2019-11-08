from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from LessonplanSchedulingProblem cimport LessonplanSchedulingProblem
from LessonplanSchedulingSolution cimport LessonplanSchedulingSolution

cdef extern from "./src/LessonplanSchedulingRandomSearchAlgorithm.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanSchedulingRandomSearchAlgorithm.hpp" namespace "lessonplans":
    cdef cppclass LessonplanSchedulingRandomSearchAlgorithm:
        LessonplanSchedulingRandomSearchAlgorithm(
                int iterations_count
        ) except +
        LessonplanSchedulingSolution* findBestLessonplan(
                LessonplanSchedulingProblem* lessonplan_scheduling_problem
        )
