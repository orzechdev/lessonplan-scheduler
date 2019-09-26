cmake_minimum_required(VERSION 3.9)
project(algorithm)
find_package(PythonInterp REQUIRED)
find_package(PythonLibs REQUIRED)
find_package(Cython REQUIRED)
find_package(PythonExtensions REQUIRED)

#set(CMAKE_CXX_STANDARD 11)

#include_directories(include/algorithm)
#include_directories(src)

add_cython_target(algorithm.pyx CXX)
#add_library(cython MODULE ${cython})

#target_link_libraries(cython ...)


#add_executable(algorithm main.cpp include/algorithm/LessonplanScheduler.hpp src/LessonplanScheduler.cpp src/GenAlgorithm.hpp src/GenAlgorithm.cpp src/LessonplanGenAlgorithm.hpp src/LessonplanGenAlgorithm.cpp)
#target_link_libraries(algorithm cython)


add_library(algorithm MODULE ${algorithm} main.cpp include/algorithm/LessonplanScheduler.hpp src/LessonplanScheduler.cpp src/GenAlgorithm.hpp src/GenAlgorithm.cpp src/LessonplanGenAlgorithm.hpp src/LessonplanGenAlgorithm.cpp)
#python_extension_module(algorithm)
python_extension_module(algorithm
        LINKED_MODULES_VAR linked_module_list
        FORWARD_DECL_MODULES_VAR fdecl_module_list)
python_modules_header(modules
        FORWARD_DECL_MODULES_LIST ${fdecl_module_list})
include_directories(${modules_INCLUDE_DIRS})
target_link_libraries(algorithm ${linked_module_list})
python_standalone_executable(algorithm)
install(TARGETS algorithm LIBRARY DESTINATION algorithm)
