# distutils: language = c++

from SchedulingProblemProperties cimport SchedulingProblemProperties
from SchedulingProblem cimport SchedulingProblem
from SchedulingGeneticAlgorithm cimport SchedulingGeneticAlgorithm
from SchedulingGreedyAlgorithm cimport SchedulingGreedyAlgorithm
from SchedulingRandomSearchAlgorithm cimport SchedulingRandomSearchAlgorithm


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
        classes_subjects_instances_number
):
    """
    Instantiate objects on the heap
    """
    scheduling_problem_properties = new SchedulingProblemProperties(
        week_days_count,
        lessons_count,
        classes_count,
        subjects_count,
        teachers_count,
        rooms_count,
        classes_subjects,
        teachers_subjects,
        rooms_subjects,
        classes_subjects_instances_number
    )

    scheduling_problem = new SchedulingProblem(
        scheduling_problem_properties
    )

    # scheduling_random_search_algorithm = new SchedulingRandomSearchAlgorithm(
    #     population_count
    # )
    scheduling_greedy_algorithm = new SchedulingGreedyAlgorithm(
        population_count
    )
    # scheduling_algorithm = new SchedulingGeneticAlgorithm(
    #     population_count,
    #     generations_count,
    #     crossover_probability,
    #     mutation_probability
    # )

    scheduling_solution = scheduling_greedy_algorithm.findBestLessonplan(
        scheduling_problem
    )

    best_lessonplan = scheduling_solution.getBestLessonplan()
    all_lessonplans = 0 # scheduling_solution.getAllLessonplans()
    all_lessonplans_hard_scores = scheduling_solution.getAllLessonplansHardScores()
    all_lessonplans_soft_scores = scheduling_solution.getAllLessonplansSoftScores()
    all_lessonplans_summary_scores = scheduling_solution.getAllLessonplansSummaryScores()

    """
    Delete heap allocated objects
    """
    del scheduling_greedy_algorithm
    del scheduling_problem
    del scheduling_problem_properties
    del scheduling_solution

    return best_lessonplan, all_lessonplans, all_lessonplans_hard_scores, all_lessonplans_soft_scores, all_lessonplans_summary_scores
