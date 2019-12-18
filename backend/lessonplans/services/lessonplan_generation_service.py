from __future__ import annotations
from enum import Enum
import os

import numpy as np

from lessonplans.algorithm.algorithm import run_random_search_algorithm, run_greedy_algorithm, run_genetic_algorithm


class AlgorithmTypes(Enum):
    RANDOM_SEARCH = 1
    GREEDY = 2
    GENETIC = 3


class LessonplanGenerationService:
    __instance = None

    __debug_print_enabled = False
    __debug_save_enabled = False
    __debug_save_dir = ""

    week_days_count = None
    lessons_count = None
    classes_count = None
    subjects_count = None
    teachers_count = None
    rooms_count = None
    classes_subjects = None
    teachers_subjects = None
    rooms_subjects = None
    classes_subjects_instances_number = None

    calculations_time_limit_in_seconds = None

    population_count = None
    crossover_probability = None
    mutation_probability = None

    def __init__(self):
        """ Virtually private constructor. """
        if LessonplanGenerationService.__instance is not None:
            raise Exception("This class is a singleton!")
        else:
            LessonplanGenerationService.__instance = self

    @staticmethod
    def get_instance() -> LessonplanGenerationService:
        """ Static access method. """
        if LessonplanGenerationService.__instance is None:
            LessonplanGenerationService()
        return LessonplanGenerationService.__instance

    def set_debug_optins(self, debug_print_enabled, debug_save_enabled, debug_save_dir):
        self.__debug_print_enabled = debug_print_enabled
        self.__debug_save_enabled = debug_save_enabled
        self.__debug_save_dir = debug_save_dir

    def set_lessonplan_data(
            self,
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
        self.week_days_count = week_days_count
        self.lessons_count = lessons_count
        self.classes_count = classes_count
        self.subjects_count = subjects_count
        self.teachers_count = teachers_count
        self.rooms_count = rooms_count
        self.classes_subjects = classes_subjects
        self.teachers_subjects = teachers_subjects
        self.rooms_subjects = rooms_subjects
        self.classes_subjects_instances_number = classes_subjects_instances_number

    def set_algorithm_calculations_time_limit(self, calculations_time_limit_in_seconds):
        self.calculations_time_limit_in_seconds = calculations_time_limit_in_seconds

    def set_algorithm_evolutionary_params(
            self,
            population_count,
            crossover_probability,
            mutation_probability
    ):
        self.population_count = population_count
        self.crossover_probability = crossover_probability
        self.mutation_probability = mutation_probability

    def generate_lessonplan(self, algorithm_type_number):
        if algorithm_type_number == AlgorithmTypes.RANDOM_SEARCH:
            if self.__debug_print_enabled:
                print('lessonplan generation started...')
            (
                best_lessonplan,
                all_lessonplans_hard_scores,
                all_lessonplans_soft_scores,
                all_lessonplans_summary_hard_scores,
                all_lessonplans_summary_soft_scores,
                best_lessonplan_score_index
            ) = run_random_search_algorithm(
                self.calculations_time_limit_in_seconds,
                self.week_days_count,
                self.lessons_count,
                self.classes_count,
                self.subjects_count,
                self.teachers_count,
                self.rooms_count,
                self.classes_subjects,
                self.teachers_subjects,
                self.rooms_subjects,
                self.classes_subjects_instances_number
            )
            if self.__debug_print_enabled:
                print('lessonplan generation finished')
                LessonplanGenerationService.__print_best_lessonplan(
                    best_lessonplan
                )
                LessonplanGenerationService.__print_best_onetime_scores(
                    all_lessonplans_hard_scores,
                    all_lessonplans_soft_scores,
                    all_lessonplans_summary_hard_scores,
                    all_lessonplans_summary_soft_scores,
                    best_lessonplan_score_index
                )
                LessonplanGenerationService.__print_onetime_results(
                    all_lessonplans_hard_scores,
                    all_lessonplans_soft_scores,
                    all_lessonplans_summary_hard_scores,
                    all_lessonplans_summary_soft_scores
                )
            if self.__debug_save_enabled:
                LessonplanGenerationService.__save_onetime_scores(
                    self.__debug_save_dir,
                    all_lessonplans_hard_scores,
                    all_lessonplans_soft_scores,
                    all_lessonplans_summary_hard_scores,
                    all_lessonplans_summary_soft_scores,
                    'random-search'
                )
        elif algorithm_type_number == AlgorithmTypes.GREEDY:
            if self.__debug_print_enabled:
                print('lessonplan generation started...')
            (
                best_lessonplan,
                all_lessonplans_hard_scores,
                all_lessonplans_soft_scores,
                all_lessonplans_summary_hard_scores,
                all_lessonplans_summary_soft_scores,
                best_lessonplan_score_index
            ) = run_greedy_algorithm(
                self.calculations_time_limit_in_seconds,
                self.week_days_count,
                self.lessons_count,
                self.classes_count,
                self.subjects_count,
                self.teachers_count,
                self.rooms_count,
                self.classes_subjects,
                self.teachers_subjects,
                self.rooms_subjects,
                self.classes_subjects_instances_number
            )
            if self.__debug_print_enabled:
                print('lessonplan generation finished')
                LessonplanGenerationService.__print_best_lessonplan(
                    best_lessonplan
                )
                LessonplanGenerationService.__print_best_onetime_scores(
                    all_lessonplans_hard_scores,
                    all_lessonplans_soft_scores,
                    all_lessonplans_summary_hard_scores,
                    all_lessonplans_summary_soft_scores,
                    best_lessonplan_score_index
                )
                LessonplanGenerationService.__print_onetime_results(
                    all_lessonplans_hard_scores,
                    all_lessonplans_soft_scores,
                    all_lessonplans_summary_hard_scores,
                    all_lessonplans_summary_soft_scores
                )
            if self.__debug_save_enabled:
                LessonplanGenerationService.__save_onetime_scores(
                    self.__debug_save_dir,
                    all_lessonplans_hard_scores,
                    all_lessonplans_soft_scores,
                    all_lessonplans_summary_hard_scores,
                    all_lessonplans_summary_soft_scores,
                    'greedy'
                )
        else:
            if self.__debug_print_enabled:
                print('lessonplan generation started...')
            (
                best_lessonplan,
                all_lessonplans_hard_scores,
                all_lessonplans_soft_scores,
                all_lessonplans_summary_hard_scores,
                all_lessonplans_summary_soft_scores,
                best_lessonplan_generation_index,
                best_lessonplan_generation_score_index
            ) = run_genetic_algorithm(
                self.calculations_time_limit_in_seconds,
                self.population_count,
                self.crossover_probability,
                self.mutation_probability,
                self.week_days_count,
                self.lessons_count,
                self.classes_count,
                self.subjects_count,
                self.teachers_count,
                self.rooms_count,
                self.classes_subjects,
                self.teachers_subjects,
                self.rooms_subjects,
                self.classes_subjects_instances_number
            )
            if self.__debug_print_enabled:
                print('lessonplan generation finished')
                LessonplanGenerationService.__print_best_lessonplan(
                    best_lessonplan
                )
                LessonplanGenerationService.__print_best_evolutionary_scores(
                    all_lessonplans_hard_scores,
                    all_lessonplans_soft_scores,
                    all_lessonplans_summary_hard_scores,
                    all_lessonplans_summary_soft_scores,
                    best_lessonplan_generation_index,
                    best_lessonplan_generation_score_index
                )
                LessonplanGenerationService.__print_evolutionary_results(
                    all_lessonplans_hard_scores,
                    all_lessonplans_soft_scores,
                    all_lessonplans_summary_hard_scores,
                    all_lessonplans_summary_soft_scores
                )
            if self.__debug_save_enabled:
                LessonplanGenerationService.__save_evolutionary_scores(
                    self.__debug_save_dir,
                    all_lessonplans_hard_scores,
                    all_lessonplans_soft_scores,
                    all_lessonplans_summary_hard_scores,
                    all_lessonplans_summary_soft_scores,
                    'genetic'
                )

    @staticmethod
    def __print_best_lessonplan(
            best_lessonplan
    ):
        print('best lessonplan')
        print(best_lessonplan)

    @staticmethod
    def __print_scores(onetime_scores):
        scores_len = len(onetime_scores)

        scores_len >= 1 and print(onetime_scores[0])
        scores_len >= 3 and print(onetime_scores[1])
        scores_len >= 5 and print(onetime_scores[2])
        scores_len >= 7 and print(onetime_scores[3])
        scores_len >= 2 and print('...')
        scores_len >= 8 and print(onetime_scores[scores_len - 4])
        scores_len >= 6 and print(onetime_scores[scores_len - 3])
        scores_len >= 4 and print(onetime_scores[scores_len - 2])
        scores_len >= 2 and print(onetime_scores[scores_len - 1])

    @staticmethod
    def __print_best_onetime_scores(
            all_lessonplans_hard_scores,
            all_lessonplans_soft_scores,
            all_lessonplans_summary_hard_scores,
            all_lessonplans_summary_soft_scores,
            best_lessonplan_score_index
    ):
        print('best lessonplan hard scores')
        print(all_lessonplans_hard_scores[best_lessonplan_score_index])
        print('best lessonplan soft scores')
        print(all_lessonplans_soft_scores[best_lessonplan_score_index])
        print('best lessonplan summary hard scores')
        print(all_lessonplans_summary_hard_scores[best_lessonplan_score_index])
        print('best lessonplan summary soft scores')
        print(all_lessonplans_summary_soft_scores[best_lessonplan_score_index])

    @staticmethod
    def __print_best_evolutionary_scores(
            all_lessonplans_hard_scores,
            all_lessonplans_soft_scores,
            all_lessonplans_summary_hard_scores,
            all_lessonplans_summary_soft_scores,
            best_lessonplan_generation_index,
            best_lessonplan_generation_score_index
    ):
        LessonplanGenerationService.__print_best_onetime_scores(
            all_lessonplans_hard_scores[best_lessonplan_generation_index],
            all_lessonplans_soft_scores[best_lessonplan_generation_index],
            all_lessonplans_summary_hard_scores[best_lessonplan_generation_index],
            all_lessonplans_summary_soft_scores[best_lessonplan_generation_index],
            best_lessonplan_generation_score_index
        )

    @staticmethod
    def __print_onetime_results(
            all_lessonplans_hard_scores,
            all_lessonplans_soft_scores,
            all_lessonplans_summary_hard_scores,
            all_lessonplans_summary_soft_scores
    ):
        print('iterations number')
        print(len(all_lessonplans_hard_scores))

        print('all lessonplans hard scores')
        LessonplanGenerationService.__print_scores(all_lessonplans_hard_scores)
        print('all lessonplans soft scores')
        LessonplanGenerationService.__print_scores(all_lessonplans_soft_scores)
        print('all lessonplans summary hard scores')
        LessonplanGenerationService.__print_scores(all_lessonplans_summary_hard_scores)
        print('all lessonplans summary soft scores')
        LessonplanGenerationService.__print_scores(all_lessonplans_summary_soft_scores)

    @staticmethod
    def __print_evolutionary_results(
            all_lessonplans_hard_scores,
            all_lessonplans_soft_scores,
            all_lessonplans_summary_hard_scores,
            all_lessonplans_summary_soft_scores
    ):
        for i in range(len(all_lessonplans_hard_scores)):
            LessonplanGenerationService.__print_onetime_results(
                all_lessonplans_hard_scores[i],
                all_lessonplans_soft_scores[i],
                all_lessonplans_summary_hard_scores[i],
                all_lessonplans_summary_soft_scores[i]
            )

    @staticmethod
    def __save_onetime_scores(
            save_dir,
            all_lessonplans_hard_scores,
            all_lessonplans_soft_scores,
            all_lessonplans_summary_hard_scores,
            all_lessonplans_summary_soft_scores,
            algorithm_type
    ):
        last_saved_data_complexity_file_path = os.path.join(save_dir, 'last_saved_data_complexity.txt')

        with open(last_saved_data_complexity_file_path) as f:
            last_data_complexity = f.read()

        np.savetxt(
            os.path.join(save_dir,
                         'all_lessonplans_hard_scores_' + algorithm_type + '_' + last_data_complexity + '.csv'),
            np.absolute(all_lessonplans_hard_scores),
            delimiter=',',
            fmt='%d'
        )
        np.savetxt(
            os.path.join(save_dir,
                         'all_lessonplans_soft_scores_' + algorithm_type + '_' + last_data_complexity + '.csv'),
            np.absolute(all_lessonplans_soft_scores),
            delimiter=',',
            fmt='%d'
        )
        np.savetxt(
            os.path.join(save_dir,
                         'all_lessonplans_summary_hard_scores_' + algorithm_type + '_' + last_data_complexity + '.csv'),
            np.absolute(all_lessonplans_summary_hard_scores),
            delimiter=',',
            fmt='%d'
        )
        np.savetxt(
            os.path.join(save_dir,
                         'all_lessonplans_summary_soft_scores_' + algorithm_type + '_' + last_data_complexity + '.csv'),
            np.absolute(all_lessonplans_summary_soft_scores),
            delimiter=',',
            fmt='%d'
        )

    @staticmethod
    def __save_evolutionary_scores(
            save_dir,
            all_lessonplans_hard_scores,
            all_lessonplans_soft_scores,
            all_lessonplans_summary_hard_scores,
            all_lessonplans_summary_soft_scores,
            algorithm_type
    ):
        last_saved_data_complexity_file_path = os.path.join(save_dir, 'last_saved_data_complexity.txt')

        with open(last_saved_data_complexity_file_path) as f:
            last_data_complexity = f.read()

        with open(
                os.path.join(
                    save_dir,
                    'all_lessonplans_hard_scores_' + algorithm_type + '_' + last_data_complexity + '.csv'
                ), 'w'
        ) as outfile:
            for idx, all_lessonplans_hard_scores_slice in enumerate(all_lessonplans_hard_scores):
                outfile.write('# Generation, ' + str(idx) + '\n')
                np.savetxt(
                    outfile,
                    np.absolute(all_lessonplans_hard_scores_slice),
                    delimiter=',',
                    fmt='%d'
                )
        with open(
                os.path.join(
                    save_dir,
                    'all_lessonplans_soft_scores_' + algorithm_type + '_' + last_data_complexity + '.csv'
                ), 'w'
        ) as outfile:
            for idx, all_lessonplans_soft_scores_slice in enumerate(all_lessonplans_soft_scores):
                outfile.write('# Generation, ' + str(idx) + '\n')
                np.savetxt(
                    outfile,
                    np.absolute(all_lessonplans_soft_scores_slice),
                    delimiter=',',
                    fmt='%d'
                )
        with open(
                os.path.join(
                    save_dir,
                    'all_lessonplans_summary_hard_scores_' + algorithm_type + '_' + last_data_complexity + '.csv'
                ), 'w'
        ) as outfile:
            for idx, all_lessonplans_summary_hard_scores_slice in enumerate(all_lessonplans_summary_hard_scores):
                outfile.write('# Generation, ' + str(idx) + '\n')
                np.savetxt(
                    outfile,
                    np.absolute(all_lessonplans_summary_hard_scores_slice),
                    delimiter=',',
                    fmt='%d'
                )
        with open(
                os.path.join(
                    save_dir,
                    'all_lessonplans_summary_soft_scores_' + algorithm_type + '_' + last_data_complexity + '.csv'
                ), 'w'
        ) as outfile:
            for idx, all_lessonplans_summary_soft_scores_slice in enumerate(all_lessonplans_summary_soft_scores):
                outfile.write('# Generation, ' + str(idx) + '\n')
                np.savetxt(
                    outfile,
                    np.absolute(all_lessonplans_summary_soft_scores_slice),
                    delimiter=',',
                    fmt='%d'
                )
