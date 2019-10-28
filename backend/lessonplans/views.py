from django.http import HttpResponse, JsonResponse

import numpy as np
import json
import os
from datetime import datetime
from lessonplans.algorithm.algorithm import run_algorithm
from lessonplans.data_validity.data_validity import is_data_valid
from lessonplans.models import *

module_dir = os.path.dirname(__file__)  # get current directory
weekdays_file_path = os.path.join(module_dir, 'predefined_data/weekdays.json')
lessons_file_path = os.path.join(module_dir, 'predefined_data/lessons.json')
subjects_file_path = os.path.join(module_dir, 'predefined_data/subjects.json')
teachers_file_path = os.path.join(module_dir, 'predefined_data/teachers.json')
classes_file_path = os.path.join(module_dir, 'predefined_data/classes.json')
rooms_file_path = os.path.join(module_dir, 'predefined_data/rooms.json')


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

    #
    # Classes
    #
    with open(classes_file_path, "r") as read_file:
        classes = json.load(read_file)

    classes_saved = []

    for class_m in classes:
        class_m_saved = Class(name=class_m['name'])
        class_m_saved.save()

        for class_m_subject in class_m['subjects']:
            for subject_idx, subject in enumerate(subjects):
                if class_m_subject['id'] == subject['id']:
                    class_subjects_rel = class_m_saved.subjects.connect(subjects_saved[subject_idx])
                    class_subjects_rel.count = class_m_subject['lessonsCount']
                    class_subjects_rel.save()
                    break

        classes_saved.append(class_m_saved)

    #
    # Rooms
    #
    with open(rooms_file_path, "r") as read_file:
        rooms = json.load(read_file)

    rooms_saved = []

    for room in rooms:
        room_saved = Room(name=room['name'])
        room_saved.save()

        for room_subject_id in room['restricted_subjects']:
            for subject_idx, subject in enumerate(subjects):
                if room_subject_id == subject['id']:
                    room_saved.restricted_subjects.connect(subjects_saved[subject_idx])
                    break

        rooms_saved.append(room_saved)

    return HttpResponse("save_data endpoint")


def get_classes(request):
    classes = Class.nodes.all()
    classes_list = [classNode.__properties__ for classNode in classes]
    return JsonResponse({"classes": classes_list})


def generate(request):
    week_days = WeekDay.nodes.all()
    lessons = Lesson.nodes.all()
    classes = Class.nodes.all()
    subjects = Subject.nodes.all()
    teachers = Teacher.nodes.all()
    rooms = Room.nodes.all()

    week_days_count = len(week_days)
    print(week_days_count)
    lessons_count = len(lessons)
    print(lessons_count)
    classes_count = len(classes)
    print(classes_count)
    subjects_count = len(subjects)
    print(subjects_count)
    teachers_count = len(teachers)
    print(teachers_count)
    rooms_count = len(rooms)
    print(rooms_count)
    classes_subjects = []
    for class_m in classes:
        class_subjects = []
        for class_subject in class_m.subjects:
            for subject_idx, subject in enumerate(subjects):
                if class_subject.id == subject.id:
                    class_subjects.append(subject_idx + 1)
        classes_subjects.append(class_subjects)
    print("START")
    print(classes_subjects)
    classes_subjects = np.array(classes_subjects, dtype=object)
    # teachers_subjects = np.array([[1, 2, 3], [2], [2, 3]], dtype=object)
    teachers_subjects = []
    for teacher in teachers:
        teacher_subjects = []
        for teacher_subject in teacher.subjects:
            for subject_idx, subject in enumerate(subjects):
                if teacher_subject.id == subject.id:
                    teacher_subjects.append(subject_idx + 1)
        teachers_subjects.append(teacher_subjects)
    # teachers_subjects = np.array(map(lambda teacher: teacher.subjects if hasattr(teacher, 'subjects') else [], teachers), dtype=object)
    print(teachers_subjects)
    teachers_subjects = np.array(teachers_subjects, dtype=object)
    # rooms_subjects = np.array([[2, 3], [2, 3], [2, 3], [2, 3], [1]], dtype=object)
    rooms_subjects = []
    for room in rooms:
        room_subjects = []
        for room_subject in room.restricted_subjects:
            for subject_idx, subject in enumerate(subjects):
                if room_subject.id == subject.id:
                    room_subjects.append(subject_idx + 1)
        rooms_subjects.append(room_subjects)
    # rooms_subjects = np.array(map(lambda room: room.restricted_subjects if hasattr(room, 'restricted_subjects') else [], rooms), dtype=object)
    print(rooms_subjects)
    rooms_subjects = np.array(rooms_subjects, dtype=object)

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

        return JsonResponse({'lessonplans': lessonplans})
    else:
        return HttpResponse("data is invalid: " + message)


def view(request):
    return HttpResponse("view endpoint")
