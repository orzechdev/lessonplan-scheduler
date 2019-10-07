import numpy as np
from lessonplans.algorithm.algorithm import run_algorithm

print("DOES IT PRINT ITSELF? - if yes, it works!")

class_count = 3
day_count = 5
lesson_count = 6
rooms = np.zeros(11, dtype=np.ushort)
teachers = np.zeros(11, dtype=np.ushort)
classes_subjects_with_classes_subjects_hours = np.zeros((11, 11, 2), dtype=np.ushort)
rooms_exclusive_assignments = np.zeros(11, dtype=np.bool)
subjects_rooms = np.zeros((11, 11), dtype=np.ushort)
teachers_subjects = np.zeros((11, 11), dtype=np.ushort)

for i in range(11):
    for j in range(11):
        classes_subjects_with_classes_subjects_hours[i][j][0] = 76
        classes_subjects_with_classes_subjects_hours[i][j][1] = 2

lessonplans = run_algorithm(
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

print(lessonplans)
