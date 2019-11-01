from django.core import serializers
from django.http import HttpResponse, JsonResponse

from setuptools import sandbox

import numpy as np
import json
import os
from datetime import datetime
from rest_framework import viewsets

from lessonplans.algorithm.algorithm import run_algorithm
from lessonplans.data_validity.data_validity import is_data_valid
from lessonplans.models import Lessonplan, WeekDay, Lesson, Subject, Teacher, TeacherSubject, Class, ClassSubject, Room, \
    RoomSubjectRestricted, LessonplanItem
from lessonplans.serializers import ClassSerializer, LessonplanSerializer, SubjectSerializer, TeacherSerializer, \
    RoomSerializer, LessonplanItemSerializer

module_dir = os.path.dirname(__file__)  # get current directory
weekdays_file_path = os.path.join(module_dir, 'predefined_data/weekdays.json')
lessons_file_path = os.path.join(module_dir, 'predefined_data/lessons.json')
subjects_file_path = os.path.join(module_dir, 'predefined_data/subjects.json')
teachers_file_path = os.path.join(module_dir, 'predefined_data/teachers.json')
classes_file_path = os.path.join(module_dir, 'predefined_data/classes.json')
rooms_file_path = os.path.join(module_dir, 'predefined_data/rooms.json')

algorithm_setup_file_path = os.path.join(module_dir, 'algorithm/setup.py')

def index(request):
    return HttpResponse("Hello, world. You're at the lessonplans index.")


def save_data(request):
    LessonplanItem.objects.all().delete()
    Lessonplan.objects.all().delete()

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


class ClassViewSet(viewsets.ModelViewSet):
    queryset = Class.objects.all()
    serializer_class = ClassSerializer


class LessonplanViewSet(viewsets.ModelViewSet):
    queryset = LessonplanItem.objects.all()
    serializer_class = LessonplanItemSerializer


def get_lessonplans(request):
    return JsonResponse({})


def generate(request):
    LessonplanItem.objects.all().delete()
    Lessonplan.objects.all().delete()

    week_days = WeekDay.objects.all()
    lessons = Lesson.objects.all()
    classes = Class.objects.all()
    subjects = Subject.objects.all()
    teachers = Teacher.objects.all()
    rooms = Room.objects.all()

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
        class_subjects = ClassSubject.objects.filter(class_model=class_m)
        class_subjects_idxs = []

        for class_subject in class_subjects:
            for subject_idx, subject in enumerate(subjects):
                if class_subject.subject.id == subject.id:
                    class_subjects_idxs.append(subject_idx + 1)

        classes_subjects.append(class_subjects_idxs)
    print(classes_subjects)
    classes_subjects = np.array(classes_subjects, dtype=object)

    teachers_subjects = []
    for teacher in teachers:
        teacher_subjects = TeacherSubject.objects.filter(teacher=teacher)
        teacher_subjects_idxs = []

        for teacher_subject in teacher_subjects:
            for subject_idx, subject in enumerate(subjects):
                if teacher_subject.subject.id == subject.id:
                    teacher_subjects_idxs.append(subject_idx + 1)

        teachers_subjects.append(teacher_subjects_idxs)
    print(teachers_subjects)
    teachers_subjects = np.array(teachers_subjects, dtype=object)

    rooms_subjects = []
    for room in rooms:
        room_subjects = RoomSubjectRestricted.objects.filter(room=room)
        room_subjects_idxs = []

        for room_subject in room_subjects:
            for subject_idx, subject in enumerate(subjects):
                if room_subject.subject.id == subject.id:
                    room_subjects_idxs.append(subject_idx + 1)

        rooms_subjects.append(room_subjects_idxs)
    print(rooms_subjects)
    rooms_subjects = np.array(rooms_subjects, dtype=object)

    validity, message = is_data_valid(classes_subjects, teachers_subjects, rooms_subjects)

    if validity:
        lessonplans_generated = run_algorithm(
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

        lessonplan = Lessonplan(name='Noname')
        lessonplan.save()

        for lessonplan_generated in lessonplans_generated:
            week_day = week_days[lessonplan_generated[0] - 1]
            lesson = lessons[lessonplan_generated[1] - 1]
            class_m = classes[lessonplan_generated[2] - 1]
            subject = subjects[lessonplan_generated[3] - 1]
            teacher = teachers[lessonplan_generated[4] - 1]
            room = rooms[lessonplan_generated[5 - 1]]

            lessonplan_item = LessonplanItem(
                lessonplan=lessonplan,
                weekday=week_day,
                lesson=lesson,
                class_model=class_m,
                subject=subject,
                teacher=teacher,
                room=room
            )
            lessonplan_item.save()

        return HttpResponse("ok")
    else:
        return HttpResponse("data is invalid: " + message)


def view(request):
    return HttpResponse("view endpoint")


def build_algorithm(request):
    sandbox.run_setup(algorithm_setup_file_path, ['build_ext', '--inplace'])

    return HttpResponse("algorithm built")

