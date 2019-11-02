# distutils: language = c++

# from LessonplanScheduler cimport LessonplanScheduler
from LessonplanSchedulingProblemProperties cimport LessonplanSchedulingProblemProperties
from LessonplanSchedulingProblem cimport LessonplanSchedulingProblem
# from LessonplanSchedulingSolution cimport LessonplanSchedulingSolution
from LessonplanSchedulingAlgorithm cimport LessonplanSchedulingAlgorithm

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
    lessonplan_scheduling_problem_properties = new LessonplanSchedulingProblemProperties(
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

    lessonplan_scheduling_problem = new LessonplanSchedulingProblem(
        lessonplan_scheduling_problem_properties
    )

    population_count = 10
    generations_count = 10
    crossover_probability = 0.2
    mutation_probability = 0.1

    lessonplan_scheduling_algorithm = new LessonplanSchedulingAlgorithm(
        population_count,
        generations_count,
        crossover_probability,
        mutation_probability
    )

    lessonplan_scheduling_solution = lessonplan_scheduling_algorithm.findBestLessonplan(
        lessonplan_scheduling_problem
    )

    best_lessonplan = lessonplan_scheduling_solution.getBestLessonplan()
    all_lessonplans = lessonplan_scheduling_solution.getAllLessonplans()
    all_lessonplans_scores = lessonplan_scheduling_solution.getAllLessonplansScores()
    all_lessonplans_summary_scores = lessonplan_scheduling_solution.getAllLessonplansSummaryScores()

    # # scheduler_ptr = new LessonplanScheduler()  # Instantiate a LessonplanScheduler object on the heap
    # try:
    #     print('try start')
    #     scheduled_lessonplan = scheduler_ptr.scheduleLessonplan(
    #         week_days_count,
    #         lessons_count,
    #         classes_count,
    #         subjects_count,
    #         teachers_count,
    #         rooms_count,
    #         classes_subjects,
    #         teachers_subjects,
    #         rooms_subjects
    #     )
    #     best_lessonplan = scheduler_ptr.getBestLessonplan()
    #     all_lessonplans = scheduler_ptr.getAllLessonplans()
    #     all_lessonplans_scores = scheduler_ptr.getAllLessonplansScores()
    #     all_lessonplans_summary_scores = scheduler_ptr.getAllLessonplansSummaryScores()
    #     print('try pass')
    # finally:
    #     print('finally')
    #     del scheduler_ptr  # delete heap allocated object
    #
    # cdef LessonplanScheduler scheduler_stack  # Instantiate a LessonplanScheduler object on the stack

    # print('scheduled lessonplan')
    # print(scheduled_lessonplan)
    print('best lessonplan')
    print(best_lessonplan)
    print('all lessonplans')
    for some_lessonplan in all_lessonplans:
        print(some_lessonplan)
    print('all lessonplans scores')
    for all_lessonplan_scores in all_lessonplans_scores:
        print(all_lessonplan_scores)
    print('all lessonplans summary scores')
    for all_lessonplan_summary_scores in all_lessonplans_summary_scores:
        print(all_lessonplan_summary_scores)

    return best_lessonplan
