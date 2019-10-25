import neomodel
from django_neomodel import DjangoNode


class Room(DjangoNode):
    uid = neomodel.UniqueIdProperty()
    name = neomodel.StringProperty()

