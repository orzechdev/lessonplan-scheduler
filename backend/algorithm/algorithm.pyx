# distutils: language = c++

from LessonplanScheduler cimport LessonplanScheduler

def run_algorithm(
        class_count,
        day_count,
        lesson_count,
        rooms,
        teachers,
        classes_subjects_with_classes_subjects_hours,
        rooms_exclusive_assignments,
        subjects_rooms,
        teachers_subjects
):
    scheduler_ptr = new LessonplanScheduler()  # Instantiate a LessonplanScheduler object on the heap
    try:
        scheduler_area = scheduler_ptr.scheduleLessonplan(
            class_count,
            day_count,
            lesson_count,
            rooms,
            teachers,
            classes_subjects_with_classes_subjects_hours,
            rooms_exclusive_assignments,
            subjects_rooms,
            teachers_subjects
        )
    finally:
        del scheduler_ptr  # delete heap allocated object

    cdef LessonplanScheduler scheduler_stack  # Instantiate a LessonplanScheduler object on the stack

    print(scheduler_area)
