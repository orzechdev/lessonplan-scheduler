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
    path('saveWeekDays/', views.save_week_days, name='saveWeekDays'),
    # path('classes/', views.get_classes, name='getClasses'),
    path('generate/', views.generate, name='generate'),
    path('view/', views.view, name='view'),
    path('buildAlgorithm', views.build_algorithm, name='buildAlgorithm'),
]
