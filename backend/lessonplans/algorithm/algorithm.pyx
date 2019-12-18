# distutils: language = c++

from SchedulingProblemProperties cimport SchedulingProblemProperties
from SchedulingProblem cimport SchedulingProblem
from SchedulingGeneticAlgorithm cimport SchedulingGeneticAlgorithm
from SchedulingGreedyAlgorithm cimport SchedulingGreedyAlgorithm
from SchedulingRandomSearchAlgorithm cimport SchedulingRandomSearchAlgorithm


def initialize_problem_instance(
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

    return scheduling_problem, scheduling_problem_properties


def run_random_search_algorithm(
        calculations_time_limit_in_seconds,
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
    scheduling_problem, scheduling_problem_properties = initialize_problem_instance(
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

    scheduling_random_search_algorithm = new SchedulingRandomSearchAlgorithm(
        calculations_time_limit_in_seconds
    )
    scheduling_solution = scheduling_random_search_algorithm.findBestLessonplan(
        scheduling_problem
    )

    best_lessonplan = scheduling_solution.getBestLessonplan()
    all_lessonplans_hard_scores = scheduling_solution.getAllLessonplansHardScores()
    all_lessonplans_soft_scores = scheduling_solution.getAllLessonplansSoftScores()
    all_lessonplans_summary_hard_scores = scheduling_solution.getAllLessonplansSummaryHardScores()
    all_lessonplans_summary_soft_scores = scheduling_solution.getAllLessonplansSummarySoftScores()
    best_lessonplan_score_index = scheduling_solution.getBestLessonplanScoreIndex()

    """
    Delete heap allocated objects
    """
    del scheduling_random_search_algorithm
    del scheduling_problem
    del scheduling_problem_properties
    del scheduling_solution

    return best_lessonplan, all_lessonplans_hard_scores, all_lessonplans_soft_scores, all_lessonplans_summary_hard_scores, all_lessonplans_summary_soft_scores, best_lessonplan_score_index


def run_greedy_algorithm(
        calculations_time_limit_in_seconds,
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
    scheduling_problem, scheduling_problem_properties = initialize_problem_instance(
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

    scheduling_greedy_algorithm = new SchedulingGreedyAlgorithm(
        calculations_time_limit_in_seconds
    )
    scheduling_solution = scheduling_greedy_algorithm.findBestLessonplan(
        scheduling_problem
    )

    best_lessonplan = scheduling_solution.getBestLessonplan()
    all_lessonplans_hard_scores = scheduling_solution.getAllLessonplansHardScores()
    all_lessonplans_soft_scores = scheduling_solution.getAllLessonplansSoftScores()
    all_lessonplans_summary_hard_scores = scheduling_solution.getAllLessonplansSummaryHardScores()
    all_lessonplans_summary_soft_scores = scheduling_solution.getAllLessonplansSummarySoftScores()
    best_lessonplan_score_index = scheduling_solution.getBestLessonplanScoreIndex()

    """
    Delete heap allocated objects
    """
    del scheduling_greedy_algorithm
    del scheduling_problem
    del scheduling_problem_properties
    del scheduling_solution

    return best_lessonplan, all_lessonplans_hard_scores, all_lessonplans_soft_scores, all_lessonplans_summary_hard_scores, all_lessonplans_summary_soft_scores, best_lessonplan_score_index


def run_genetic_algorithm(
        calculations_time_limit_in_seconds,
        population_count,
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
    scheduling_problem, scheduling_problem_properties = initialize_problem_instance(
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

    scheduling_genetic_algorithm = new SchedulingGeneticAlgorithm(
        calculations_time_limit_in_seconds,
        population_count,
        crossover_probability,
        mutation_probability
    )
    scheduling_evolutional_solution = scheduling_genetic_algorithm.findBestLessonplan(
        scheduling_problem
    )

    best_lessonplan = scheduling_evolutional_solution.getBestLessonplan()
    all_lessonplans_hard_scores = scheduling_evolutional_solution.getAllLessonplansHardScores()
    all_lessonplans_soft_scores = scheduling_evolutional_solution.getAllLessonplansSoftScores()
    all_lessonplans_summary_hard_scores = scheduling_evolutional_solution.getAllLessonplansSummaryHardScores()
    all_lessonplans_summary_soft_scores = scheduling_evolutional_solution.getAllLessonplansSummarySoftScores()
    best_lessonplan_generation_index = scheduling_evolutional_solution.getBestLessonplanGenerationIndex()
    best_lessonplan_generation_score_index = scheduling_evolutional_solution.getBestLessonplanGenerationScoreIndex()

    """
    Delete heap allocated objects
    """
    del scheduling_genetic_algorithm
    del scheduling_problem
    del scheduling_problem_properties
    del scheduling_evolutional_solution

    return best_lessonplan, all_lessonplans_hard_scores, all_lessonplans_soft_scores, all_lessonplans_summary_hard_scores, all_lessonplans_summary_soft_scores, best_lessonplan_generation_index, best_lessonplan_generation_score_index
