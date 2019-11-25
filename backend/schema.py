import graphene

import lessonplans.schema


class Query(lessonplans.schema.Query, graphene.ObjectType):
    pass


class Mutation(lessonplans.schema.Mutation, graphene.ObjectType):
    pass


schema = graphene.Schema(query=Query, mutation=Mutation)
