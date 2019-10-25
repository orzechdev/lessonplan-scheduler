from django.http import HttpResponse, JsonResponse

import numpy as np
import json
import os
from datetime import datetime
from lessonplans.algorithm.algorithm import run_algorithm
from lessonplans.models import *

module_dir = os.path.dirname(__file__)  # get current directory
weekdays_file_path = os.path.join(module_dir, 'predefined_data/weekdays.json')
lessons_file_path = os.path.join(module_dir, 'predefined_data/lessons.json')
subjects_file_path = os.path.join(module_dir, 'predefined_data/subjects.json')
teachers_file_path = os.path.join(module_dir, 'predefined_data/teachers.json')


def index(request):
    return HttpResponse("Hello, world. You're at the lessonplans index.")


def save_data(request):
    #
    # Weekdays
    #
    with open(weekdays_file_path, "r") as read_file:
        weekdays = json.load(read_file)

    weekdays_saved = []

    for weekday in weekdays:
        weekday_saved = WeekDay(name=weekday['name'])
        weekday_saved.save()

        weekdays_saved.append(weekday_saved)

    #
    # Lessons
    #
    with open(lessons_file_path, "r") as read_file:
        lessons = json.load(read_file)

    lessons_saved = []

    for lesson in lessons:
        start_datetime = datetime.strptime(lesson['startTime'], '%H:%M')
        end_datetime = datetime.strptime(lesson['endTime'], '%H:%M')
        lesson_saved = Lesson(name=lesson['name'], startTime=start_datetime, endTime=end_datetime)
        lesson_saved.save()

        lessons_saved.append(lesson_saved)

    #
    # Subjects
    #
    with open(subjects_file_path, "r") as read_file:
        subjects = json.load(read_file)

    subjects_saved = []

    for subject in subjects:
        subject_saved = Subject(name=subject['name'])
        subject_saved.save()

        subjects_saved.append(subject_saved)

    #
    # Teachers
    #
    with open(teachers_file_path, "r") as read_file:
        teachers = json.load(read_file)

    teachers_saved = []

    for teacher in teachers:
        teacher_saved = Teacher(name=teacher['name'])
        teacher_saved.save()

        for teacher_subject_id in teacher['subjects']:
            for subject_idx, subject in enumerate(subjects):
                if teacher_subject_id == subject['id']:
                    teacher_saved.subjects.connect(subjects_saved[subject_idx])
                    break

        teachers_saved.append(teacher_saved)

    # teacher_1.subjects.connect(subject_1)
    # teacher_1.subjects.connect(subject_2)
    #
    # teacher_2.subjects.connect(subject_4)

    return HttpResponse("save_data endpoint")


def generate(request):
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

    return JsonResponse({'lessonplans': lessonplans})


def view(request):
    return HttpResponse("view endpoint")
