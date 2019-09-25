import numpy as np
from algorithm.algorithm import run_algorithm

print("DOES IT PRINT ITSELF? - if yes, it works!")

lessons = np.zeros(11)
rooms = np.zeros(11)
subjects = np.zeros(11)
teachers = np.zeros(11)
classes = np.zeros(11)

run_algorithm(
        lessons,
        rooms,
        subjects,
        teachers,
        classes
)
