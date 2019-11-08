from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

from LessonplanSchedulingProblem cimport LessonplanSchedulingProblem
from LessonplanSchedulingSolution cimport LessonplanSchedulingSolution

cdef extern from "./src/LessonplanSchedulingGeneticAlgorithm.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanSchedulingGeneticAlgorithm.hpp" namespace "lessonplans":
    cdef cppclass LessonplanSchedulingGeneticAlgorithm:
        LessonplanSchedulingGeneticAlgorithm(
                int population_count,
                int generations_count,
                float crossover_probability,
                float mutation_probability
        ) except +
        LessonplanSchedulingSolution* findBestLessonplan(
                LessonplanSchedulingProblem* lessonplan_scheduling_problem
        )
