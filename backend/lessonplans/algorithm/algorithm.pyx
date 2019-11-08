# distutils: language = c++

from LessonplanSchedulingProblemProperties cimport LessonplanSchedulingProblemProperties
from LessonplanSchedulingProblem cimport LessonplanSchedulingProblem
from LessonplanSchedulingGeneticAlgorithm cimport LessonplanSchedulingGeneticAlgorithm
from LessonplanSchedulingRandomSearchAlgorithm cimport LessonplanSchedulingRandomSearchAlgorithm

def run_algorithm(
        population_count,
        generations_count,
        crossover_probability,
        mutation_probability,
        week_days_count,
        lessons_count,
        classes_count,
        subjects_count,
        teachers_count,
        rooms_count,
        classes_subjects,
        teachers_subjects,
        rooms_subjects,
        classes_subjects_count
):
    """
    Instantiate objects on the heap
    """
    lessonplan_scheduling_problem_properties = new LessonplanSchedulingProblemProperties(
        week_days_count,
        lessons_count,
        classes_count,
        subjects_count,
        teachers_count,
        rooms_count,
        classes_subjects,
        teachers_subjects,
        rooms_subjects,
        classes_subjects_count
    )

    lessonplan_scheduling_problem = new LessonplanSchedulingProblem(
        lessonplan_scheduling_problem_properties
    )

    lessonplan_scheduling_random_search_algorithm = new LessonplanSchedulingRandomSearchAlgorithm(
        population_count
    )
    # lessonplan_scheduling_algorithm = new LessonplanSchedulingGeneticAlgorithm(
    #     population_count,
    #     generations_count,
    #     crossover_probability,
    #     mutation_probability
    # )

    lessonplan_scheduling_solution = lessonplan_scheduling_random_search_algorithm.findBestLessonplan(
        lessonplan_scheduling_problem
    )

    best_lessonplan = lessonplan_scheduling_solution.getBestLessonplan()
    all_lessonplans = lessonplan_scheduling_solution.getAllLessonplans()
    all_lessonplans_hard_scores = lessonplan_scheduling_solution.getAllLessonplansHardScores()
    all_lessonplans_soft_scores = lessonplan_scheduling_solution.getAllLessonplansSoftScores()
    all_lessonplans_summary_scores = lessonplan_scheduling_solution.getAllLessonplansSummaryScores()

    print('best lessonplan')
    print(best_lessonplan)
    print('all lessonplans')
    for some_lessonplan in all_lessonplans:
        print(some_lessonplan)
    print('all lessonplans hard scores')
    for all_lessonplan_hard_scores in all_lessonplans_hard_scores:
        print(all_lessonplan_hard_scores)
    print('all lessonplans soft scores')
    for all_lessonplan_soft_scores in all_lessonplans_soft_scores:
        print(all_lessonplan_soft_scores)
    print('all lessonplans summary scores')
    for all_lessonplan_summary_scores in all_lessonplans_summary_scores:
        print(all_lessonplan_summary_scores)

    """
    Delete heap allocated objects
    """
    del lessonplan_scheduling_random_search_algorithm
    del lessonplan_scheduling_problem
    del lessonplan_scheduling_problem_properties
    del lessonplan_scheduling_solution

    return best_lessonplan
