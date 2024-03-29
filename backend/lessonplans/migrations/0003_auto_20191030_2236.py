# Generated by Django 2.2.6 on 2019-10-30 22:36

from django.db import migrations


class Migration(migrations.Migration):

    dependencies = [
        ('lessonplans', '0002_auto_20191029_0121'),
    ]

    operations = [
        migrations.RenameField(
            model_name='lessonplanitem',
            old_name='class_id',
            new_name='class_model',
        ),
        migrations.RenameField(
            model_name='lessonplanitem',
            old_name='lesson_id',
            new_name='lesson',
        ),
        migrations.RenameField(
            model_name='lessonplanitem',
            old_name='lessonplan_id',
            new_name='lessonplan',
        ),
        migrations.RenameField(
            model_name='lessonplanitem',
            old_name='room_id',
            new_name='room',
        ),
        migrations.RenameField(
            model_name='lessonplanitem',
            old_name='subject_id',
            new_name='subject',
        ),
        migrations.RenameField(
            model_name='lessonplanitem',
            old_name='teacher_id',
            new_name='teacher',
        ),
        migrations.RenameField(
            model_name='lessonplanitem',
            old_name='weekday_id',
            new_name='weekday',
        ),
    ]
