from libcpp.vector cimport vector
from libcpp cimport bool
from numpy import ushort

cdef extern from "./src/LessonplanSchedulingSolution.cpp":
    pass

cdef extern from "./include/algorithm/LessonplanSchedulingSolution.hpp" namespace "lessonplans":
    cdef cppclass LessonplanSchedulingSolution:
        vector[vector[ushort]] getBestLessonplan()
        vector[vector[vector[ushort]]] getAllLessonplans()
        vector[vector[int]] getAllLessonplansScores()
        vector[int] getAllLessonplansSummaryScores()
