from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from SchedulingProblem cimport SchedulingProblem
from SchedulingSolution cimport SchedulingSolution

cdef extern from "./src/SchedulingGeneticAlgorithm.cpp":
    pass

cdef extern from "./include/algorithm/SchedulingGeneticAlgorithm.hpp" namespace "lessonplans":
    cdef cppclass SchedulingGeneticAlgorithm:
        SchedulingGeneticAlgorithm(
                int population_count,
                int generations_count,
                float crossover_probability,
                float mutation_probability
        ) except +
        SchedulingSolution* findBestLessonplan(
                SchedulingProblem* scheduling_problem
        )