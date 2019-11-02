from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from LessonplanSchedulingProblem cimport LessonplanSchedulingProblem
from LessonplanSchedulingSolution cimport LessonplanSchedulingSolution

cdef extern from "./src/LessonplanSchedulingAlgorithm.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanSchedulingAlgorithm.hpp" namespace "lessonplans":
    cdef cppclass LessonplanSchedulingAlgorithm:
        LessonplanSchedulingAlgorithm(
                int population_count,
                int generations_count,
                float crossover_probability,
                float mutation_probability
        ) except +
        LessonplanSchedulingSolution* findBestLessonplan(
                LessonplanSchedulingProblem* lessonplan_scheduling_problem
        )
