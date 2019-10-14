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
classes_subjects = np.zeros((2, 3), dtype=np.ushort)
teachers_subjects_restriction_status = np.ones(3, dtype=np.ushort)
teachers_subjects = np.zeros((3, 3), dtype=np.ushort)
rooms_subjects_restriction_status = np.zeros(5, dtype=np.ushort)
rooms_subjects = np.zeros((5, 3), dtype=np.ushort)

classes_subjects[0][0] = 1
classes_subjects[0][1] = 2
classes_subjects[0][2] = 3
classes_subjects[1][0] = 1
classes_subjects[1][1] = 3

teachers_subjects[0][0] = 1
teachers_subjects[0][1] = 2
teachers_subjects[0][2] = 3
teachers_subjects[1][0] = 2
teachers_subjects[2][0] = 2
teachers_subjects[2][1] = 3

rooms_subjects_restriction_status[0] = 1
rooms_subjects[0][0] = 2
rooms_subjects[0][1] = 3
rooms_subjects_restriction_status[1] = 1
rooms_subjects[1][0] = 2
rooms_subjects[1][1] = 3
rooms_subjects_restriction_status[2] = 1
rooms_subjects[2][0] = 2
rooms_subjects[2][1] = 3
rooms_subjects_restriction_status[3] = 1
rooms_subjects[3][0] = 2
rooms_subjects[3][1] = 3
rooms_subjects_restriction_status[4] = 1
rooms_subjects[4][0] = 1


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
