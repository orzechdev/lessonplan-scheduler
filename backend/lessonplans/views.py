from django.http import HttpResponse, JsonResponse

from setuptools import sandbox

import numpy as np
import json
import os
from datetime import datetime
from rest_framework import viewsets

from lessonplans.services.lessonplan_generation_service import AlgorithmTypes, LessonplanGenerationService
from lessonplans.data_validity.data_validity import is_data_valid
from lessonplans.models import Lessonplan, WeekDay, Lesson, Subject, Teacher, TeacherSubject, Class, ClassSubject, Room, \
    RoomSubjectRestricted, LessonplanItem
from lessonplans.serializers import ClassSerializer, LessonplanItemSerializer

module_dir = os.path.dirname(__file__)  # get current directory

algorithm_setup_file_path = os.path.join(module_dir, 'algorithm/setup.py')

all_lessonplans_hard_scores_image_path = os.path.join(module_dir, 'algorithm_tests/all_lessonplans_hard_scores.png')
all_lessonplans_soft_scores_image_path = os.path.join(module_dir, 'algorithm_tests/all_lessonplans_soft_scores.png')
all_lessonplans_summary_hard_scores_image_path = os.path.join(module_dir, 'algorithm_tests/all_lessonplans_summary_hard_scores.png')
all_lessonplans_summary_soft_scores_image_path = os.path.join(module_dir, 'algorithm_tests/all_lessonplans_summary_soft_scores.png')

all_lessonplans_scores_file_path = os.path.join(module_dir, 'algorithm_tests')
all_lessonplans_soft_scores_file_path = os.path.join(module_dir, 'algorithm_tests/all_lessonplans_soft_scores.npy')
all_lessonplans_summary_hard_scores_file_path = os.path.join(module_dir, 'algorithm_tests/all_lessonplans_summary_hard_scores.npy')
all_lessonplans_summary_soft_scores_file_path = os.path.join(module_dir, 'algorithm_tests/all_lessonplans_summary_soft_scores.npy')

last_saved_data_complexity_file_path = os.path.join(all_lessonplans_scores_file_path, 'last_saved_data_complexity.txt')


def index(request):
    return HttpResponse("Hello, world. You're at the lessonplans index.")


def save_week_days(request):
    week_days = WeekDay.objects.all()

    if len(week_days) <= 0:
        data_complexity_dir = 'low_complexity'
        weekdays_file_path = os.path.join(module_dir, 'test_data/' + data_complexity_dir + '/weekdays.json')

        with open(weekdays_file_path, "r") as read_file:
            weekdays = json.load(read_file)

        weekdays_saved = []

        for weekday in weekdays:
            weekday_saved = WeekDay(name=weekday['name'])
            weekday_saved.save()

            weekdays_saved.append(weekday_saved)

        return HttpResponse("save_week_days saved")

    return HttpResponse("save_week_days exist")


def save_data(request):
    data_complexity = request.GET.get('data-complexity')
    just_lessons = False

    if data_complexity == 'high':
        data_complexity_dir = 'high_complexity'
    elif data_complexity == 'medium':
        data_complexity_dir = 'medium_complexity'
    elif data_complexity == 'just_lessons':
        data_complexity_dir = 'low_complexity'
        just_lessons = True
    else:
        data_complexity_dir = 'low_complexity'

    with open(last_saved_data_complexity_file_path, "w") as text_file:
        text_file.write(data_complexity)

    weekdays_file_path = os.path.join(module_dir, 'test_data/' + data_complexity_dir + '/weekdays.json')
    lessons_file_path = os.path.join(module_dir, 'test_data/' + data_complexity_dir + '/lessons.json')
    subjects_file_path = os.path.join(module_dir, 'test_data/' + data_complexity_dir + '/subjects.json')
    teachers_file_path = os.path.join(module_dir, 'test_data/' + data_complexity_dir + '/teachers.json')
    classes_file_path = os.path.join(module_dir, 'test_data/' + data_complexity_dir + '/classes.json')
    rooms_file_path = os.path.join(module_dir, 'test_data/' + data_complexity_dir + '/rooms.json')

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

    if just_lessons:
        return HttpResponse("save_data endpoint")

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


def get_data():
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

    return (
        week_days,
        lessons,
        classes,
        subjects,
        teachers,
        rooms,
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


def generate(request):
    (
        week_days,
        lessons,
        classes,
        subjects,
        teachers,
        rooms,
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
    ) = get_data()

    validity, message = is_data_valid(classes_subjects, teachers_subjects, rooms_subjects)

    if not validity:
        return HttpResponse("data is invalid: " + message)
    else:
        LessonplanItem.objects.all().delete()
        Lessonplan.objects.all().delete()

        lessonplan_generation_service = LessonplanGenerationService.get_instance()
        lessonplan_generation_service.set_debug_optins(
            debug_print_enabled=True,
            debug_save_enabled=True,
            debug_save_dir=all_lessonplans_scores_file_path
        )
        lessonplan_generation_service.set_lessonplan_data(
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
        lessonplan_generation_service.set_algorithm_calculations_time_limit(
            calculations_time_limit_in_seconds=60
        )

        algorithm_type = request.GET.get('algorithm-type')

        if algorithm_type == 'random-search':
            best_lessonplan, best_hard_scores, best_soft_scores = lessonplan_generation_service.generate_lessonplan(
                AlgorithmTypes.RANDOM_SEARCH
            )
        elif algorithm_type == 'greedy':
            best_lessonplan, best_hard_scores, best_soft_scores = lessonplan_generation_service.generate_lessonplan(
                AlgorithmTypes.GREEDY
            )
        else:
            lessonplan_generation_service.set_algorithm_evolutionary_params(
                population_count=80,
                crossover_probability=0.01,
                mutation_probability=0.8
            )
            best_lessonplan, best_hard_scores, best_soft_scores = lessonplan_generation_service.generate_lessonplan(
                AlgorithmTypes.GENETIC
            )

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

        return JsonResponse({
            'algorithmType': algorithm_type,
            'result': 'ok',
            'lessonplanHardScores': [
                {
                    'id': 'invalidClassSubjectSameLessonsTimes',
                    'description': 'More then one activities for class occurring at the same time',
                    'value': 0 - best_hard_scores[0]
                },
                {
                    'id': 'invalidTeacherSameLessonsTimes',
                    'description': 'More then one activities for teacher occurring at the same time',
                    'value': 0 - best_hard_scores[1]
                },
                {
                    'id': 'invalidRoomSameLessonTimes',
                    'description': 'More then one activities for room occurring at the same time',
                    'value': 0 - best_hard_scores[2]
                },
                {
                    'id': 'invalidTeacherChangesForClassesSubjects',
                    'description': 'Different teachers assigned for one class subject',
                    'value': 0 - best_hard_scores[3]
                }
            ],
            'lessonplanSoftScores': [
                {
                    'id': 'invalidDifferenceBetweenStartLessons',
                    'description': 'Invalid differences between start lessons in each week day',
                    'value': 0 - best_soft_scores[0]
                },
                {
                    'id': 'invalidDifferenceBetweenLessonsCount',
                    'description': 'Invalid differences between lessons count in each week day',
                    'value': 0 - best_soft_scores[1]
                },
                {
                    'id': 'invalidFreePeriodsCountBetweenLessons',
                    'description': 'Invalid free periods count between lessons',
                    'value': 0 - best_soft_scores[2]
                }
            ]
        })


def view(request):
    return HttpResponse("view endpoint")


def build_algorithm(request):
    sandbox.run_setup(algorithm_setup_file_path, ['build_ext', '--inplace'])

    return HttpResponse("algorithm built")
