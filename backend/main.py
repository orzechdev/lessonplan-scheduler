import numpy as np
from lessonplans.algorithm.algorithm import run_algorithm

print("DOES IT PRINT ITSELF? - if yes, it works!")

week_days_count = 2
lessons_count = 3
classes_count = 2
subjects_count = 3
teachers_count = 3
rooms_count = 5
classes_subjects_restriction_status = np.ones(2, dtype=np.ushort)
classes_subjects = np.array([[1, 3], [1, 2, 3]], dtype=object)
teachers_subjects_restriction_status = np.ones(3, dtype=np.ushort)
teachers_subjects = np.array([[1, 2, 3], [2], [2, 3]], dtype=object)
rooms_subjects_restriction_status = np.zeros(5, dtype=np.ushort)
rooms_subjects = np.array([[2, 3], [2, 3], [2, 3], [2, 3], [1]], dtype=object)

rooms_subjects_restriction_status[0] = 1
rooms_subjects_restriction_status[1] = 1
rooms_subjects_restriction_status[2] = 1
rooms_subjects_restriction_status[3] = 1
rooms_subjects_restriction_status[4] = 1


lessonplans = run_algorithm(
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

print(lessonplans)
