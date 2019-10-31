# distutils: language = c++

from LessonplanScheduler cimport LessonplanScheduler

def run_algorithm(
        week_days_count,
        lessons_count,
        classes_count,
        subjects_count,
        teachers_count,
        rooms_count,
        classes_subjects,
        teachers_subjects,
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
            classes_subjects,
            teachers_subjects,
            rooms_subjects
        )
        best_lessonplan = scheduler_ptr.getBestLessonplan()
        all_lessonplans = scheduler_ptr.getAllLessonplans()
        all_lessonplans_grades = scheduler_ptr.getAllLessonplansGrades()
        all_lessonplans_grades_sums = scheduler_ptr.getAllLessonplansGradesSums()
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
    for some_lessonplan in all_lessonplans:
        print(some_lessonplan)
    print('all lessonplans grades')
    for some_lessonplan_grades in all_lessonplans_grades:
        print(some_lessonplan_grades)
    print('all lessonplans grades sums')
    for some_lessonplan_grades_sum in all_lessonplans_grades_sums:
        print(some_lessonplan_grades_sum)

    return scheduled_lessonplan
