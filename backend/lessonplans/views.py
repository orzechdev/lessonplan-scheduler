from django.core import serializers
from django.http import HttpResponse, JsonResponse

from setuptools import sandbox

import numpy as np
import json
import os
from datetime import datetime
from rest_framework import viewsets

from lessonplans.algorithm.algorithm import AlgorithmTypes, run_algorithm
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


def print_scores(scores):
    print(scores[0])
    print(scores[1])
    print(scores[2])
    print(scores[3])
    print('...')
    scores_len = len(scores)
    print(scores[scores_len - 4])
    print(scores[scores_len - 3])
    print(scores[scores_len - 2])
    print(scores[scores_len - 1])


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

    print('data count')
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
    classes_subjects_instances_number = []
    for class_m in classes:
        class_subjects = ClassSubject.objects.filter(class_model=class_m)
        class_subjects_idxs = []
        class_subjects_count = []

        for class_subject in class_subjects:
            for subject_idx, subject in enumerate(subjects):
                if class_subject.subject.id == subject.id:
                    class_subjects_idxs.append(subject_idx + 1)
                    class_subjects_count.append(class_subject.count_in_week)

        classes_subjects.append(class_subjects_idxs)
        classes_subjects_instances_number.append(class_subjects_count)
    print('classes subjects')
    print(classes_subjects)
    classes_subjects = np.array(classes_subjects, dtype=object)
    print('classes subjects instances number')
    print(classes_subjects_instances_number)
    classes_subjects_instances_number = np.array(classes_subjects_instances_number, dtype=object)

    teachers_subjects = []
    for teacher in teachers:
        teacher_subjects = TeacherSubject.objects.filter(teacher=teacher)
        teacher_subjects_idxs = []

        for teacher_subject in teacher_subjects:
            for subject_idx, subject in enumerate(subjects):
                if teacher_subject.subject.id == subject.id:
                    teacher_subjects_idxs.append(subject_idx + 1)

        teachers_subjects.append(teacher_subjects_idxs)
    print('teachers subjects')
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
    print('rooms subjects')
    print(rooms_subjects)
    rooms_subjects = np.array(rooms_subjects, dtype=object)

    validity, message = is_data_valid(classes_subjects, teachers_subjects, rooms_subjects)

    if validity:
        population_count = 30
        generations_count = 10
        crossover_probability = 0.2
        mutation_probability = 0.1

        print('lessonplan generation started...')

        best_lessonplan, all_lessonplans_hard_scores, all_lessonplans_soft_scores, all_lessonplans_summary_hard_scores, all_lessonplans_summary_soft_scores, best_lessonplan_score_index = run_algorithm(
            AlgorithmTypes.GREEDY,
            population_count,
            generations_count,
            crossover_probability,
            mutation_probability,
            week_days_count,
            lessons_count,
            classes_count,
            subjects_count,
            teachers_count,
            rooms_count,
            classes_subjects,
            teachers_subjects,
            rooms_subjects,
            classes_subjects_instances_number
        )

        print('lessonplan generation finished')

        print('best lessonplan')
        print(best_lessonplan)

        print('best lessonplan hard scores')
        print(all_lessonplans_hard_scores[best_lessonplan_score_index])
        print('best lessonplan soft scores')
        print(all_lessonplans_soft_scores[best_lessonplan_score_index])
        print('best lessonplan summary hard scores')
        print(all_lessonplans_summary_hard_scores[best_lessonplan_score_index])
        print('best lessonplan summary soft scores')
        print(all_lessonplans_summary_soft_scores[best_lessonplan_score_index])

        print('all lessonplans hard scores')
        print_scores(all_lessonplans_hard_scores)
        print('all lessonplans soft scores')
        print_scores(all_lessonplans_soft_scores)
        print('all lessonplans summary hard scores')
        print_scores(all_lessonplans_summary_hard_scores)
        print('all lessonplans summary soft scores')
        print_scores(all_lessonplans_summary_soft_scores)

        lessonplan = Lessonplan(name='Noname')
        lessonplan.save()

        for best_lessonplan_data_item in best_lessonplan:
            week_day = week_days[best_lessonplan_data_item[0] - 1]
            lesson = lessons[best_lessonplan_data_item[1] - 1]
            class_m = classes[best_lessonplan_data_item[2] - 1]
            subject = subjects[best_lessonplan_data_item[3] - 1]
            teacher = teachers[best_lessonplan_data_item[4] - 1]
            room = rooms[best_lessonplan_data_item[5] - 1]

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
