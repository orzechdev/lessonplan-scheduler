from rest_framework import serializers

from lessonplans.models import Class, Lessonplan, ClassSubject, TeacherSubject


class ClassSerializer(serializers.HyperlinkedModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = Class
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


class LessonplanSerializer(serializers.HyperlinkedModelSerializer):
    id = serializers.ReadOnlyField()

    class Meta:
        model = Lessonplan
        fields = '__all__'

