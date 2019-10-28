import numpy as np
from lessonplans.algorithm.algorithm import run_algorithm
from lessonplans.data_validity.data_validity import is_data_valid

print("DOES IT PRINT ITSELF? - if yes, it works!")

# week_days_count = 2
# lessons_count = 3
# classes_count = 2
# subjects_count = 3
# teachers_count = 3
# rooms_count = 5
# classes_subjects_restriction_status = np.ones(2, dtype=np.ushort)
# classes_subjects = np.array([[1, 3], [1, 2, 3]], dtype=object)
# teachers_subjects_restriction_status = np.ones(3, dtype=np.ushort)
# teachers_subjects = np.array([[1, 2, 3], [2], [2, 3]], dtype=object)
# rooms_subjects_restriction_status = np.zeros(5, dtype=np.ushort)
# rooms_subjects = np.array([[2, 3], [2, 3], [2, 3], [2, 3], [1]], dtype=object)


week_days_count = 5
lessons_count = 8
classes_count = 16
subjects_count = 20
teachers_count = 24
rooms_count = 29
classes_subjects = np.array([[19], [19], [19], [19], [19], [16, 15, 14, 13, 8, 6, 5, 4, 2, 1], [16, 15, 14, 13, 8, 6, 5, 4, 2, 1], [16, 15, 14, 13, 10, 9, 6, 5, 4, 2, 1], [16, 15, 14, 13, 10, 9, 6, 5, 4, 2, 1], [16, 15, 14, 13, 10, 9, 6, 5, 4, 2, 1], [16, 15, 14, 13, 10, 9, 6, 5, 4, 2, 1], [19], [16, 14, 13, 12, 11, 10, 9, 6, 5, 4, 3, 2, 1], [16, 14, 13, 12, 11, 10, 9, 6, 5, 4, 3, 2, 1], [17, 16, 14, 13, 12, 11, 10, 9, 7, 6, 3, 2, 1], [17, 16, 14, 13, 12, 11, 10, 9, 7, 6, 3, 2, 1]], dtype=object)
teachers_subjects = np.array([[7, 6], [5, 4], [1], [3], [2], [9, 8], [11, 10, 8], [15, 14], [16], [2], [3], [1], [5, 4], [9, 7, 6], [2], [13, 12], [11, 10, 8], [13, 12], [15, 14], [2], [17, 16], [19], [19], [19]], dtype=object)
rooms_subjects = np.array([[16], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [16]], dtype=object)


# week_days_count = 5
# lessons_count = 8
# classes_count = 1
# subjects_count = 20
# teachers_count = 24
# rooms_count = 29
# classes_subjects = np.array([[18, 16, 15, 14, 13, 8, 6, 5, 4, 2, 1]], dtype=object)
# teachers_subjects = np.array([[7, 6], [5, 4], [1], [3], [2], [9, 8], [11, 10, 8], [15, 14], [16], [2], [3], [1], [5, 4], [9, 7, 6], [2], [13, 12], [11, 10, 8], [13, 12], [15, 14], [2], [17, 16], [19, 18], [19], [19]], dtype=object)
# rooms_subjects = np.array([[16], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [16]], dtype=object)


validity, message = is_data_valid(classes_subjects, teachers_subjects, rooms_subjects)

if validity:
    lessonplans = run_algorithm(
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

    print(lessonplans)
else:
    print("data is invalid")
    print(message)
