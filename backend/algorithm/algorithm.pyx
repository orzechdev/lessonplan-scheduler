# distutils: language = c++

from LessonplanScheduler cimport LessonplanScheduler

def run_algorithm(
        lessons,
        rooms,
        subjects,
        teachers,
        classes
):
    scheduler_ptr = new LessonplanScheduler()  # Instantiate a LessonplanScheduler object on the heap
    try:
        scheduler_area = scheduler_ptr.scheduleLessonplan(
            lessons,
            rooms,
            subjects,
            teachers,
            classes
        )
    finally:
        del scheduler_ptr  # delete heap allocated object

    cdef LessonplanScheduler scheduler_stack  # Instantiate a LessonplanScheduler object on the stack

    print(scheduler_area)
