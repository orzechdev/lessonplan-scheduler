from rest_framework import serializers

from lessonplans.models import Class, Lessonplan, ClassSubject, TeacherSubject, Subject, Teacher, Room, WeekDay, Lesson, \
    LessonplanItem


class WeekDaySerializer(serializers.ModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = WeekDay
        fields = '__all__'


class LessonSerializer(serializers.ModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = Lesson
        fields = '__all__'


class ClassSerializer(serializers.ModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = Class
        fields = '__all__'


class SubjectSerializer(serializers.ModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = Subject
        fields = '__all__'


class TeacherSerializer(serializers.ModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = Teacher
        fields = '__all__'


class RoomSerializer(serializers.ModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = Room
        fields = '__all__'


class ClassSubjectSerializer(serializers.HyperlinkedModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = ClassSubject
        fields = '__all__'


class TeacherSubjectSerializer(serializers.HyperlinkedModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = TeacherSubject
        fields = '__all__'


class LessonplanSerializer(serializers.ModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = Lessonplan
        fields = '__all__'


class LessonplanItemSerializer(serializers.HyperlinkedModelSerializer):
    id = serializers.ReadOnlyField()
    lessonplan = WeekDaySerializer(many=False)
    weekday = WeekDaySerializer(many=False)
    lesson = LessonSerializer(many=False)
    class_model = ClassSerializer(many=False)
    subject = SubjectSerializer(many=False)
    teacher = TeacherSerializer(many=False)
    room = RoomSerializer(many=False)

    class Meta:
        model = LessonplanItem
        fields = ("id", "lessonplan", "weekday", "lesson", "class_model", "subject", "teacher", "room")

