from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

cdef extern from "./src/algorithm/SchedulingSolution.cpp":
    pass

cdef extern from "./include/algorithm/SchedulingSolution.hpp" namespace "lessonplans":
    cdef cppclass SchedulingSolution:
        vector[vector[ushort]] getBestLessonplan()
        vector[vector[int]] getAllLessonplansHardScores()
        vector[vector[int]] getAllLessonplansSoftScores()
        vector[int] getAllLessonplansSummaryHardScores()
        vector[int] getAllLessonplansSummarySoftScores()
        int getBestLessonplanScoreIndex()
