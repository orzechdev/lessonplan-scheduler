from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from SchedulingProblem cimport SchedulingProblem
from SchedulingSolution cimport SchedulingSolution

cdef extern from "./src/algorithm/genetic/SchedulingGeneticAlgorithm.cpp":
    pass

cdef extern from "./include/algorithm/genetic/SchedulingGeneticAlgorithm.hpp" namespace "lessonplans":
    cdef cppclass SchedulingGeneticAlgorithm:
        SchedulingGeneticAlgorithm(
                int calculations_time_limit_in_seconds,
                int population_count,
                float crossover_probability,
                float mutation_probability
        ) except +
        SchedulingSolution* findBestLessonplan(
                SchedulingProblem* scheduling_problem
        )
