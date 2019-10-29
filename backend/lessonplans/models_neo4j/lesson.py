import neomodel
from django_neomodel import DjangoNode


class Lesson(DjangoNode):
    uid = neomodel.UniqueIdProperty()
    name = neomodel.IntegerProperty()
    startTime = neomodel.DateTimeProperty()
    endTime = neomodel.DateTimeProperty()

