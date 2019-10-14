# distutils: language = c++

from LessonplanScheduler cimport LessonplanScheduler

def run_algorithm(
        week_days_count,
        lessons_count,
        classes_count,
        subjects_count,
        teachers_count,
        rooms_count,
        classes_subjects_restriction_status,
        classes_subjects,
        teachers_subjects_restriction_status,
        teachers_subjects,
        rooms_subjects_restriction_status,
        rooms_subjects
):
    scheduler_ptr = new LessonplanScheduler()  # Instantiate a LessonplanScheduler object on the heap
    try:
        print('aa 1')
        scheduler_area = scheduler_ptr.scheduleLessonplan(
            week_days_count,
            lessons_count,
            classes_count,
            subjects_count,
            teachers_count,
            rooms_count,
            classes_subjects_restriction_status,
            classes_subjects,
            teachers_subjects_restriction_status,
            teachers_subjects,
            rooms_subjects_restriction_status,
            rooms_subjects
        )
        print('aa 2')
    finally:
        print('bb 1')
        del scheduler_ptr  # delete heap allocated object

    cdef LessonplanScheduler scheduler_stack  # Instantiate a LessonplanScheduler object on the stack

    print('ee')
    print(scheduler_area)

    return scheduler_area
