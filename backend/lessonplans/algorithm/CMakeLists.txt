cmake_minimum_required(VERSION 3.10)
project(algorithm)

#find_package(PythonInterp REQUIRED)
#find_package(PythonLibs REQUIRED)

#find_package(Cython REQUIRED)
#find_package(PythonExtensions REQUIRED)

set(CMAKE_CXX_STANDARD 11)

#include_directories(include/algorithm)
#include_directories(src)

#add_cython_target(algorithm algorithm.pyx)
#add_library(cython MODULE ${cython})

#target_link_libraries(cython ...)


#add_executable(algorithm main.cpp include/algorithm/LessonplanScheduler.hpp src/LessonplanScheduler.cpp src/SchedulingGeneticAlgorithm.hpp src/SchedulingGeneticAlgorithm.cpp src/LessonplanGenAlgorithm.hpp src/LessonplanGenAlgorithm.cpp)
add_executable(
        algorithm
        include/algorithm/genetic/SchedulingGeneticAlgorithm.hpp
        src/algorithm/genetic/SchedulingGeneticAlgorithm.cpp
        include/lessonplan/LessonplanIndividual.hpp
        src/lessonplan/LessonplanIndividual.cpp
        include/lessonplan/LessonplanIndividualFactory.hpp
        src/lessonplan/LessonplanIndividualFactory.cpp
        include/algorithm/SchedulingProblemProperties.hpp
        src/algorithm/SchedulingProblemProperties.cpp
        include/algorithm/SchedulingProblem.hpp
        src/algorithm/SchedulingProblem.cpp
        include/algorithm/SchedulingSolution.hpp
        src/algorithm/SchedulingSolution.cpp
        include/algorithm/greedy/SchedulingGreedyAlgorithm.hpp
        src/algorithm/greedy/SchedulingGreedyAlgorithm.cpp
        include/algorithm/random-search/SchedulingRandomSearchAlgorithm.hpp
        src/algorithm/random-search/SchedulingRandomSearchAlgorithm.cpp
        include/utils/RandomNumberGenerator.hpp
        src/utils/RandomNumberGenerator.cpp
        include/lessonplan/LessonplanIndividualDescriptor.hpp
        src/lessonplan/LessonplanIndividualDescriptor.cpp
)
#target_link_libraries(algorithm cython)


#add_library(algorithm MODULE ${cython} main.cpp include/algorithm/LessonplanScheduler.hpp src/LessonplanScheduler.cpp src/SchedulingGeneticAlgorithm.hpp src/SchedulingGeneticAlgorithm.cpp src/LessonplanGenAlgorithm.hpp src/LessonplanGenAlgorithm.cpp)
#python_extension_module(algorithm)
#install(TARGETS algorithm LIBRARY DESTINATION algorithm)
