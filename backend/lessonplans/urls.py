from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('saveData/', views.save_data, name='saveData'),
    path('classes/', views.get_classes, name='getClasses'),
    path('generate/', views.generate, name='generate'),
    path('view/', views.view, name='view'),
]
