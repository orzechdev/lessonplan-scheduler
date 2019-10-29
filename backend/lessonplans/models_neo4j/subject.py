import neomodel
from django_neomodel import DjangoNode

# from lessonplans.models.room import Room


class Subject(DjangoNode):
    uid = neomodel.UniqueIdProperty()
    name = neomodel.StringProperty()
    # restricted_rooms = neomodel.Relationship(
    #     Room,
    #     rel_type='restricted to'
    # )

