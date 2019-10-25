import neomodel
from django_neomodel import DjangoNode


class Subject(DjangoNode):
    uid = neomodel.UniqueIdProperty()
    name = neomodel.StringProperty()

