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
        print('try start')
        scheduled_lessonplan = scheduler_ptr.scheduleLessonplan(
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
        best_lessonplan = scheduler_ptr.getBestLessonplan()
        all_lessonplans = scheduler_ptr.getAllLessonplans()
        print('try pass')
    finally:
        print('finally')
        del scheduler_ptr  # delete heap allocated object

    cdef LessonplanScheduler scheduler_stack  # Instantiate a LessonplanScheduler object on the stack

    print('scheduled lessonplan')
    print(scheduled_lessonplan)
    print('best lessonplan')
    print(best_lessonplan)
    print('all lessonplans')
    print(all_lessonplans)

    return scheduled_lessonplan
