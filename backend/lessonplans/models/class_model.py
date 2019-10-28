import neomodel
from django_neomodel import DjangoNode

from lessonplans.models.subject import Subject


class ClassSubjectsRelationship(neomodel.StructuredRel):
    count = neomodel.IntegerProperty(default=1)


class Class(DjangoNode):
    uid = neomodel.UniqueIdProperty()
    name = neomodel.StringProperty()
    subjects = neomodel.Relationship(
        Subject,
        rel_type='learns',
        model=ClassSubjectsRelationship
    )

