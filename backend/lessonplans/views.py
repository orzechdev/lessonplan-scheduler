from django.http import HttpResponse, JsonResponse

import numpy as np
import json
import os
from datetime import datetime
from lessonplans.algorithm.algorithm import run_algorithm
from lessonplans.data_validity.data_validity import is_data_valid
from lessonplans.models import Lessonplan, WeekDay, Lesson, Subject, Teacher, TeacherSubject, Class, ClassSubject, Room, \
    RoomSubjectRestricted

from lessonplans.views_neo4j import save_data_to_neo4j, generate_with_neo4j, get_classes_with_neo4j

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
    RoomSubjectRestricted.objects.all().delete()
    ClassSubject.objects.all().delete()
    TeacherSubject.objects.all().delete()
    Room.objects.all().delete()
    Class.objects.all().delete()
    Teacher.objects.all().delete()
    Subject.objects.all().delete()
    Lesson.objects.all().delete()
    WeekDay.objects.all().delete()

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
        lesson_saved = Lesson(name=lesson['name'], start_time=start_datetime, end_time=end_datetime)
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

        teachers_saved.append(teacher_saved)

        for teacher_subject_id in teacher['subjects']:
            for subject_idx, subject in enumerate(subjects):
                if teacher_subject_id == subject['id']:
                    teacher_subject_saved = TeacherSubject(
                        teacher=teacher_saved,
                        subject=subjects_saved[subject_idx]
                    )
                    teacher_subject_saved.save()
                    break

    #
    # Classes
    #
    with open(classes_file_path, "r") as read_file:
        classes = json.load(read_file)

    classes_saved = []

    for class_m in classes:
        class_m_saved = Class(name=class_m['name'])
        class_m_saved.save()

        classes_saved.append(class_m_saved)

        for class_m_subject in class_m['subjects']:
            for subject_idx, subject in enumerate(subjects):
                if class_m_subject['id'] == subject['id']:
                    class_m_subject_saved = ClassSubject(
                        class_model=class_m_saved,
                        subject=subjects_saved[subject_idx],
                        count_in_week=class_m_subject['lessonsCount']
                    )
                    class_m_subject_saved.save()
                    break

    #
    # Rooms
    #
    with open(rooms_file_path, "r") as read_file:
        rooms = json.load(read_file)

    rooms_saved = []

    for room in rooms:
        room_saved = Room(name=room['name'])
        room_saved.save()

        rooms_saved.append(room_saved)

        for room_subject_id in room['restricted_subjects']:
            for subject_idx, subject in enumerate(subjects):
                if room_subject_id == subject['id']:
                    room_subject_restricted_saved = RoomSubjectRestricted(
                        room=room_saved,
                        subject=subjects_saved[subject_idx]
                    )
                    room_subject_restricted_saved.save()
                    break

    return HttpResponse("save_data endpoint")


def save_data_to_neo4j_pass(request):
    save_data_to_neo4j(request)


def get_classes(request):
    get_classes_with_neo4j(request)


def get_lessonplans(request):
    return JsonResponse({})


def generate(request):
    generate_with_neo4j(request)


def view(request):
    return HttpResponse("view endpoint")
