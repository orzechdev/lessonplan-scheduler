from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

cdef extern from "./src/algorithm/SchedulingEvolutionalSolution.cpp":
    pass

cdef extern from "./include/algorithm/SchedulingEvolutionalSolution.hpp" namespace "lessonplans":
    cdef cppclass SchedulingEvolutionalSolution:
        vector[vector[ushort]] getBestLessonplan()
        vector[vector[vector[int]]] getAllLessonplansHardScores()
        vector[vector[vector[int]]] getAllLessonplansSoftScores()
        vector[vector[int]] getAllLessonplansSummaryHardScores()
        vector[vector[int]] getAllLessonplansSummarySoftScores()
        int getBestLessonplanGenerationIndex()
        int getBestLessonplanGenerationScoreIndex()
