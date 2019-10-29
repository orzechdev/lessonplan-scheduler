from django.db import models


class WeekDay(models.Model):
    name = models.CharField(max_length=50)


class Lesson(models.Model):
    name = models.IntegerField()
    start_time = models.TimeField()
    end_time = models.TimeField()


class Class(models.Model):
    name = models.CharField(max_length=50)


class Room(models.Model):
    name = models.CharField(max_length=50)


class Subject(models.Model):
    name = models.CharField(max_length=50)


class Teacher(models.Model):
    name = models.CharField(max_length=50)


class ClassSubject(models.Model):
    class_model = models.ForeignKey(Class, on_delete=models.CASCADE)
    subject = models.ForeignKey(Subject, on_delete=models.CASCADE)
    count_in_week = models.IntegerField(default=1)


class RoomSubjectRestricted(models.Model):
    room = models.ForeignKey(Room, on_delete=models.CASCADE)
    subject = models.ForeignKey(Subject, on_delete=models.CASCADE)


class SubjectRoomRestricted(models.Model):
    subject = models.ForeignKey(Subject, on_delete=models.CASCADE)
    room = models.ForeignKey(Room, on_delete=models.CASCADE)


class TeacherSubject(models.Model):
    teacher = models.ForeignKey(Teacher, on_delete=models.CASCADE)
    subject = models.ForeignKey(Subject, on_delete=models.CASCADE)


class Lessonplan(models.Model):
    name = models.CharField(max_length=50)


class LessonplanItem(models.Model):
    lessonplan_id = models.ForeignKey(Lessonplan, on_delete=models.CASCADE)
    weekday_id = models.ForeignKey(WeekDay, on_delete=models.CASCADE)
    lesson_id = models.ForeignKey(Lesson, on_delete=models.CASCADE)
    class_id = models.ForeignKey(Class, on_delete=models.CASCADE)
    subject_id = models.ForeignKey(Subject, on_delete=models.CASCADE)
    teacher_id = models.ForeignKey(Teacher, on_delete=models.CASCADE)
    room_id = models.ForeignKey(Room, on_delete=models.CASCADE)

