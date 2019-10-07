# distutils: language = c++

from LessonplanScheduler cimport LessonplanScheduler

def run_algorithm(
        lessons_restrictions_for_individuals,
        weekdays_restrictions_for_individuals,
        rooms_restrictions_for_individuals,
        teachers_restrictions_for_individuals,
        classes_restrictions_for_individuals,
        subjects_restrictions_for_individuals
):
    scheduler_ptr = new LessonplanScheduler()  # Instantiate a LessonplanScheduler object on the heap
    try:
        print('aa 1')
        scheduler_area = scheduler_ptr.scheduleLessonplan(
            lessons_restrictions_for_individuals,
            weekdays_restrictions_for_individuals,
            rooms_restrictions_for_individuals,
            teachers_restrictions_for_individuals,
            classes_restrictions_for_individuals,
            subjects_restrictions_for_individuals
        )
        print('aa 2')
    finally:
        print('bb 1')
        del scheduler_ptr  # delete heap allocated object

    cdef LessonplanScheduler scheduler_stack  # Instantiate a LessonplanScheduler object on the stack

    print('ee')
    print(scheduler_area)

    return scheduler_area
