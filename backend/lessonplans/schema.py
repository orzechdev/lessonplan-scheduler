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

    weekday = graphene.Field(WeekDayType, id=graphene.Int())
    lesson = graphene.Field(LessonType, id=graphene.Int())
    class_model = graphene.Field(ClassType, id=graphene.Int(), name=graphene.String())
    room = graphene.Field(RoomType, id=graphene.Int())
    subject = graphene.Field(SubjectType, id=graphene.Int())
    teacher = graphene.Field(TeacherType, id=graphene.Int())

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
    def resolve_weekday(_, info, **kwargs):
        id = kwargs.get('id')

        if id is not None:
            return WeekDay.objects.get(pk=id)

        return None

    @staticmethod
    def resolve_lesson(_, info, **kwargs):
        id = kwargs.get('id')

        if id is not None:
            return Lesson.objects.get(pk=id)

        return None

    @staticmethod
    def resolve_class_model(_, info, **kwargs):
        id = kwargs.get('id')
        name = kwargs.get('name')

        if id is not None:
            return Class.objects.get(pk=id)

        if name is not None:
            return Class.objects.get(name=name)

        return None

    @staticmethod
    def resolve_room(_, info, **kwargs):
        id = kwargs.get('id')

        if id is not None:
            return Room.objects.get(pk=id)

        return None

    @staticmethod
    def resolve_subject(_, info, **kwargs):
        id = kwargs.get('id')

        if id is not None:
            return Subject.objects.get(pk=id)

        return None

    @staticmethod
    def resolve_teacher(_, info, **kwargs):
        id = kwargs.get('id')

        if id is not None:
            return Teacher.objects.get(pk=id)

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
            subject_count_in_week = getattr(subject_input, 'count_in_week', 1)
            if subject_count_in_week >= 1:
                subject = Subject.objects.get(pk=subject_input.id)
                class_subject = ClassSubject(class_model=class_model, subject=subject, count_in_week=subject_count_in_week)
                class_subject.save()
                class_subjects.append(class_subject)
        return CreateClassMutation(class_model=class_model, class_subjects=class_subjects)

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


class UpdateLessonMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)
        name = graphene.Int(required=True)
        start_time = graphene.Time(required=True)
        end_time = graphene.Time(required=True)

    lesson = graphene.Field(LessonType)

    def mutate(self, info, id, name, start_time, end_time):
        lesson = Lesson.objects.get(pk=id)
        lesson.name = name
        lesson.start_time = start_time
        lesson.end_time = end_time
        lesson.save()
        return UpdateLessonMutation(lesson=lesson)


class UpdateRoomMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)
        name = graphene.String(required=True)

    room = graphene.Field(RoomType)

    def mutate(self, info, id, name):
        room = Room.objects.get(pk=id)
        room.name = name
        room.save()
        return UpdateRoomMutation(room=room)


class UpdateSubjectMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)
        name = graphene.String(required=True)

    subject = graphene.Field(SubjectType)

    def mutate(self, info, id, name):
        subject = Subject.objects.get(pk=id)
        subject.name = name
        subject.save()
        return UpdateSubjectMutation(subject=subject)


class UpdateTeacherMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)
        name = graphene.String(required=True)
        subjects_ids = graphene.List(graphene.types.Int, required=True)

    teacher = graphene.Field(TeacherType)
    teacher_subjects = graphene.List(SubjectType)

    def mutate(self, info, id, name, subjects_ids):
        teacher = Teacher.objects.get(pk=id)
        teacher.name = name
        teacher.save()
        TeacherSubject.objects.filter(teacher=teacher).delete()
        teacher_subjects = []
        for subject_id in subjects_ids:
            subject = Subject.objects.get(pk=subject_id)
            teacher_subject = TeacherSubject(teacher=teacher, subject=subject)
            teacher_subject.save()
            teacher_subjects.append(subject)
        return UpdateTeacherMutation(teacher=teacher, teacher_subjects=teacher_subjects)


class UpdateClassMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)
        name = graphene.String(required=True)
        subjects = graphene.List(ClassSubjectInput, required=True)

    class_model = graphene.Field(ClassType)
    class_subjects = graphene.List(ClassSubjectType)

    def mutate(self, info, id, name, subjects):
        class_model = Class.objects.get(pk=id)
        class_model.name = name
        class_model.save()
        ClassSubject.objects.filter(class_model=class_model).delete()
        class_subjects = []
        for subject_input in subjects:
            subject_count_in_week = getattr(subject_input, 'count_in_week', 1)
            if subject_count_in_week >= 1:
                subject = Subject.objects.get(pk=subject_input.id)
                class_subject = ClassSubject(class_model=class_model, subject=subject, count_in_week=subject_count_in_week)
                class_subject.save()
                class_subjects.append(class_subject)
        return UpdateClassMutation(class_model=class_model, class_subjects=class_subjects)


class DeleteLessonMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)

    ok = graphene.Boolean()

    def mutate(self, info, id):
        lesson = Lesson.objects.get(pk=id)
        lesson.delete()
        return DeleteLessonMutation(ok=True)


class DeleteRoomMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)

    ok = graphene.Boolean()

    def mutate(self, info, id):
        room = Room.objects.get(pk=id)
        room.delete()
        return DeleteRoomMutation(ok=True)


class DeleteSubjectMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)

    ok = graphene.Boolean()

    def mutate(self, info, id):
        subject = Subject.objects.get(pk=id)
        subject.delete()
        return DeleteSubjectMutation(ok=True)


class DeleteTeacherMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)

    ok = graphene.Boolean()

    def mutate(self, info, id):
        teacher = Teacher.objects.get(pk=id)
        teacher.delete()
        return DeleteTeacherMutation(ok=True)


class DeleteClassMutation(graphene.Mutation):
    class Arguments:
        id = graphene.Int(required=True)

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
    update_lesson = UpdateLessonMutation.Field()
    update_room = UpdateRoomMutation.Field()
    update_subject = UpdateSubjectMutation.Field()
    update_teacher = UpdateTeacherMutation.Field()
    update_class = UpdateClassMutation.Field()
    delete_lesson = DeleteLessonMutation.Field()
    delete_room = DeleteRoomMutation.Field()
    delete_subject = DeleteSubjectMutation.Field()
    delete_teacher = DeleteTeacherMutation.Field()
    delete_class = DeleteClassMutation.Field()
    create_teacher_subject_bulk = CreateTeacherSubjectBulkMutation.Field()

