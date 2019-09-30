import numpy as np
from algorithm.algorithm import run_algorithm

print("DOES IT PRINT ITSELF? - if yes, it works!")

day_count = 5
lesson_count = 8
rooms = np.zeros(11)
subjects = np.zeros(11)
teachers = np.zeros(11)
classes = np.zeros(11)

run_algorithm(
        day_count,
        lesson_count,
        rooms,
        subjects,
        teachers,
        classes
)
