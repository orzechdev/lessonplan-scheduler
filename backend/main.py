import numpy as np
from lessonplans.algorithm.algorithm import run_algorithm

print("DOES IT PRINT ITSELF? - if yes, it works!")

# class_count = 3
# day_count = 5
# lesson_count = 6
# rooms = np.zeros(11, dtype=np.ushort)
# teachers = np.zeros(11, dtype=np.ushort)
# classes_subjects_with_classes_subjects_hours = np.zeros((11, 11, 2), dtype=np.ushort)
# rooms_exclusive_assignments = np.zeros(11, dtype=np.bool)
# subjects_rooms = np.zeros((11, 11), dtype=np.ushort)
# teachers_subjects = np.zeros((11, 11), dtype=np.ushort)
#
# for i in range(11):
#     for j in range(11):
#         classes_subjects_with_classes_subjects_hours[i][j][0] = 76
#         classes_subjects_with_classes_subjects_hours[i][j][1] = 2
#
# lessonplans = run_algorithm(
#     class_count,
#     day_count,
#     lesson_count,
#     rooms,
#     teachers,
#     classes_subjects_with_classes_subjects_hours,
#     rooms_exclusive_assignments,
#     subjects_rooms,
#     teachers_subjects
# )

related_data_types = 5
max_data_count = 3
relation_rules = 3

lessons_restrictions_for_individuals = np.zeros((3, related_data_types, max_data_count, relation_rules), dtype=np.ushort)
weekdays_restrictions_for_individuals = np.zeros((2, related_data_types, max_data_count, relation_rules), dtype=np.ushort)
rooms_restrictions_for_individuals = np.zeros((3, related_data_types, max_data_count, relation_rules), dtype=np.ushort)
teachers_restrictions_for_individuals = np.zeros((2, related_data_types, max_data_count, relation_rules), dtype=np.ushort)
classes_restrictions_for_individuals = np.zeros((2, related_data_types, max_data_count, relation_rules), dtype=np.ushort)
subjects_restrictions_for_individuals = np.zeros((3, related_data_types, max_data_count, relation_rules), dtype=np.ushort)

for i in range(3):
    for j in range(related_data_types):
        for k in range(max_data_count):
            lessons_restrictions_for_individuals[i][j][k][0] = 1000
            lessons_restrictions_for_individuals[i][j][k][1] = 0
            lessons_restrictions_for_individuals[i][j][k][2] = 1

for i in range(2):
    for j in range(related_data_types):
        for k in range(max_data_count):
            weekdays_restrictions_for_individuals[i][j][k][0] = 1000
            weekdays_restrictions_for_individuals[i][j][k][1] = 0
            weekdays_restrictions_for_individuals[i][j][k][2] = 1

# to change
for i in range(2):
    for j in range(related_data_types):
        for k in range(max_data_count):
            classes_restrictions_for_individuals[i][j][k][0] = 1000
            classes_restrictions_for_individuals[i][j][k][1] = 0
            classes_restrictions_for_individuals[i][j][k][2] = 1

lessonplans = run_algorithm(
    lessons_restrictions_for_individuals,
    weekdays_restrictions_for_individuals,
    rooms_restrictions_for_individuals,
    teachers_restrictions_for_individuals,
    classes_restrictions_for_individuals,
    subjects_restrictions_for_individuals
)

print(lessonplans)
