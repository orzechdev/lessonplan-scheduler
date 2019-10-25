import neomodel
from django_neomodel import DjangoNode

from lessonplans.models.subject import Subject


class Teacher(DjangoNode):
    uid = neomodel.UniqueIdProperty()
    name = neomodel.StringProperty()
    subjects = neomodel.Relationship(
        Subject,
        rel_type='teaches'
    )

