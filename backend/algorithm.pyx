# distutils: language = c++

from LessonplanScheduler cimport LessonplanScheduler

def run_algorithm():
    scheduler_ptr = new LessonplanScheduler(2, 5)  # Instantiate a LessonplanScheduler object on the heap
    try:
        scheduler_area = scheduler_ptr.scheduleLessonplan()
    finally:
        del scheduler_ptr  # delete heap allocated object

    cdef LessonplanScheduler scheduler_stack  # Instantiate a LessonplanScheduler object on the stack

    print(scheduler_area)
