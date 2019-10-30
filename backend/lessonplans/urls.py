from django.urls import path, include
from rest_framework import routers

from . import views

router = routers.DefaultRouter()
router.register(r'classes', views.ClassViewSet)
router.register(r'lessonplans', views.LessonplanViewSet)

urlpatterns = [
    path('', include(router.urls)),
    path('', views.index, name='index'),
    path('saveData/', views.save_data, name='saveData'),
    path('saveDataToNeo4j', views.save_data_to_neo4j_pass, name='saveDataToNeo4j'),
    # path('classes/', views.get_classes, name='getClasses'),
    path('generate/', views.generate, name='generate'),
    path('generateFromNeo4j', views.generate_with_neo4j_pass, name='generateFromNeo4j'),
    path('view/', views.view, name='view'),
]
