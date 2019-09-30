import numpy as np
from algorithm.algorithm import run_algorithm

print("DOES IT PRINT ITSELF? - if yes, it works!")

day_count = 5
lesson_count = 8
rooms = np.zeros(11, dtype=np.ushort)
subjects = np.zeros(11, dtype=np.ushort)
teachers = np.zeros(11, dtype=np.ushort)
classes = np.zeros(11, dtype=np.ushort)

run_algorithm(
        day_count,
        lesson_count,
        rooms,
        subjects,
        teachers,
        classes
)
