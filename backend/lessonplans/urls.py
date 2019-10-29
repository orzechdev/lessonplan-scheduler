from django.urls import path

from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('saveData/', views.save_data, name='saveData'),
    path('saveDataToNeo4j', views.save_data_to_neo4j_pass, name='saveDataToNeo4j'),
    path('classes/', views.get_classes, name='getClasses'),
    path('generate/', views.generate, name='generate'),
    path('view/', views.view, name='view'),
]
