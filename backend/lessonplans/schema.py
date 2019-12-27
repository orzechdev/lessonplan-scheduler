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

    teacher = graphene.Field(TeacherType)

    def mutate(self, info, name, subjects):
        teacher = Teacher(name=name)
        teacher.save()
        return CreateTeacherMutation(teacher=teacher)


class CreateClassMutation(graphene.Mutation):
    class Arguments:
        name = graphene.String(required=True)

    class_model = graphene.Field(ClassType)

    def mutate(self, info, name):
        class_model = Class(name=name)
        class_model.save()
        return CreateClassMutation(class_model=class_model)


class CreateTeacherSubjectMutation(graphene.Mutation):
    class Arguments:
        teacher_id = graphene.Int(required=True)
        subject_id = graphene.Int(required=True)

    teacher_subject = graphene.Field(TeacherSubjectType)

    def mutate(self, info, teacher_id, subject_id):
        teacher_subject = TeacherSubject(teacher_id=teacher_id, subject_id=subject_id)
        teacher_subject.save()
        return CreateTeacherSubjectMutation(teacher_subject=teacher_subject)


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

