import graphene

from graphene_django.types import DjangoObjectType

from lessonplans.models import WeekDay, Lesson, Class, Room, Subject, Teacher, ClassSubject, RoomSubjectRestricted, \
    SubjectRoomRestricted, TeacherSubject, Lessonplan, LessonplanItem


class WeekDayType(DjangoObjectType):
    class Meta:
        model = WeekDay


class LessonType(DjangoObjectType):
    class Meta:
        model = Lesson


class ClassType(DjangoObjectType):
    class Meta:
        model = Class


class RoomType(DjangoObjectType):
    class Meta:
        model = Room


class SubjectType(DjangoObjectType):
    class Meta:
        model = Subject


class TeacherType(DjangoObjectType):
    class Meta:
        model = Teacher


class ClassSubjectType(DjangoObjectType):
    class Meta:
        model = ClassSubject


class RoomSubjectRestrictedType(DjangoObjectType):
    class Meta:
        model = RoomSubjectRestricted


class SubjectRoomRestrictedType(DjangoObjectType):
    class Meta:
        model = SubjectRoomRestricted


class TeacherSubjectType(DjangoObjectType):
    class Meta:
        model = TeacherSubject


class LessonplanType(DjangoObjectType):
    class Meta:
        model = Lessonplan


class LessonplanItemType(DjangoObjectType):
    class Meta:
        model = LessonplanItem


class Query(object):
    all_weekdays = graphene.List(WeekDayType)
    all_lessons = graphene.List(LessonType)
    all_classes = graphene.List(ClassType)
    all_rooms = graphene.List(RoomType)
    all_subjects = graphene.List(SubjectType)
    all_teachers = graphene.List(TeacherType)
    all_lessonplans = graphene.List(LessonplanType)
    all_lessonplans_items = graphene.List(LessonplanItemType)

    class_model = graphene.Field(ClassType, id=graphene.Int(), name=graphene.String())

    @staticmethod
    def resolve_all_weekdays(_, info, **kwargs):
        return WeekDay.objects.all()

    @staticmethod
    def resolve_all_lessons(_, info, **kwargs):
        return Lesson.objects.all()

    @staticmethod
    def resolve_all_classes(_, info, **kwargs):
        return Class.objects.all()

    @staticmethod
    def resolve_all_rooms(_, info, **kwargs):
        return Room.objects.all()

    @staticmethod
    def resolve_all_subjects(_, info, **kwargs):
        return Subject.objects.all()

    @staticmethod
    def resolve_all_teachers(_, info, **kwargs):
        return Teacher.objects.all()

    @staticmethod
    def resolve_all_lessonplans(_, info, **kwargs):
        return Lessonplan.objects.all()

    @staticmethod
    def resolve_all_lessonplans_items(_, info, **kwargs):
        return LessonplanItem.objects.all()

    @staticmethod
    def resolve_class_model(_, info, **kwargs):
        id = kwargs.get('id')
        name = kwargs.get('name')

        if id is not None:
            return Class.objects.get(pk=id)

        if name is not None:
            return Class.objects.get(name=name)

        return None


class CreateLessonMutation(graphene.Mutation):
    class Arguments:
        name = graphene.String(required=True)
        start_time = graphene.Time(required=True)
        end_time = graphene.Time(required=True)

    lesson = graphene.Field(LessonType)

    def mutate(self, info, name, start_time, end_time):
        lesson = Lesson(name=name, start_time=start_time, end_time=end_time)
        lesson.save()
        return CreateLessonMutation(lesson=lesson)


class CreateRoomMutation(graphene.Mutation):
    class Arguments:
        name = graphene.String(required=True)

    room = graphene.Field(RoomType)

    def mutate(self, info, name):
        room = Room(name=name)
        room.save()
        return CreateRoomMutation(room=room)


class CreateSubjectMutation(graphene.Mutation):
    class Arguments:
        name = graphene.String(required=True)

    subject = graphene.Field(SubjectType)

    def mutate(self, info, name):
        subject = Subject(name=name)
        subject.save()
        return CreateSubjectMutation(subject=subject)


class CreateTeacherMutation(graphene.Mutation):
    class Arguments:
        name = graphene.String(required=True)
        subjects_ids = graphene.List(graphene.types.Int, required=True)

    teacher = graphene.Field(TeacherType)
    teacher_subjects = graphene.List(SubjectType)

    def mutate(self, info, name, subjects_ids):
        teacher = Teacher(name=name)
        teacher.save()
        teacher_subjects = []
        for subject_id in subjects_ids:
            subject = Subject.objects.get(pk=subject_id)
            teacher_subject = TeacherSubject(teacher=teacher, subject=subject)
            teacher_subject.save()
            teacher_subjects.append(subject)
        return CreateTeacherMutation(teacher=teacher, teacher_subjects=teacher_subjects)


class ClassSubjectInput(graphene.InputObjectType):
    id = graphene.Int(required=True)
    count_in_week = graphene.Int()


class CreateClassMutation(graphene.Mutation):
    class Arguments:
        name = graphene.String(required=True)
        subjects = graphene.List(ClassSubjectInput, required=True)

    class_model = graphene.Field(ClassType)
    class_subjects = graphene.List(ClassSubjectType)

    def mutate(self, info, name, subjects):
        class_model = Class(name=name)
        class_model.save()
        class_subjects = []
        for subject_input in subjects:
            subject = Subject.objects.get(pk=subject_input.id)
            class_subject = ClassSubject(class_model=class_model, subject=subject, count_in_week=subject.count_in_week)
            class_subject.save()
            class_subjects.append(class_subject)
        return CreateClassMutation(class_model=class_model)

#
# class CreateTeacherSubjectMutation(graphene.Mutation):
#     class Arguments:
#         teacher_id = graphene.Int(required=True)
#         subject_id = graphene.Int(required=True)
#
#     teacher_subject = graphene.Field(TeacherSubjectType)
#
#     def mutate(self, info, teacher_id, subject_id):
#         teacher_subject = TeacherSubject(teacher_id=teacher_id, subject_id=subject_id)
#         teacher_subject.save()
#         return CreateTeacherSubjectMutation(teacher_subject=teacher_subject)


class TeacherSubjectInput(graphene.InputObjectType):
    id = graphene.ID(required=True)


class CreateTeacherSubjectBulkMutation(graphene.Mutation):
    class Arguments:
        teacher_id = graphene.Int(required=True)
        teacher_subjects_ids = graphene.List(graphene.types.Int)

    teacher_subjects = graphene.List(TeacherSubjectType)

    def mutate(self, info, teacher_id, teacher_subjects_ids):
        teacher_subjects = []
        for teacher_subject_id in teacher_subjects_ids:
            teacher = Teacher.objects.get(pk=teacher_id)
            subject = Subject.objects.get(pk=teacher_subject_id)
            teacher_subject = TeacherSubject(teacher=teacher, subject=subject)
            teacher_subject.save()
            teacher_subjects.append(teacher_subject)
        return CreateTeacherSubjectBulkMutation(teacher_subjects=teacher_subjects)


class DeleteClassMutation(graphene.Mutation):
    class Arguments:
        id = graphene.ID(required=True)

    ok = graphene.Boolean()

    def mutate(self, info, id):
        class_model = Class.objects.get(pk=id)
        class_model.delete()
        return DeleteClassMutation(ok=True)


class Mutation(object):
    create_lesson = CreateLessonMutation.Field()
    create_room = CreateRoomMutation.Field()
    create_subject = CreateSubjectMutation.Field()
    create_teacher = CreateTeacherMutation.Field()
    create_class = CreateClassMutation.Field()
    delete_class = DeleteClassMutation.Field()
    create_teacher_subject_bulk = CreateTeacherSubjectBulkMutation.Field()

