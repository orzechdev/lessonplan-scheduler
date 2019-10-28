import neomodel
from django_neomodel import DjangoNode

from lessonplans.models.subject import Subject


class Room(DjangoNode):
    uid = neomodel.UniqueIdProperty()
    name = neomodel.StringProperty()
    restricted_subjects = neomodel.Relationship(
        Subject,
        rel_type='restricted to'
    )

