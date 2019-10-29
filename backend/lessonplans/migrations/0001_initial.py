# Generated by Django 2.2.6 on 2019-10-29 00:27

from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='Class',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=50)),
            ],
        ),
        migrations.CreateModel(
            name='Lesson',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.IntegerField()),
                ('startTime', models.TimeField()),
                ('endTime', models.TimeField()),
            ],
        ),
        migrations.CreateModel(
            name='Lessonplan',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=50)),
            ],
        ),
        migrations.CreateModel(
            name='Room',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=50)),
            ],
        ),
        migrations.CreateModel(
            name='Subject',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=50)),
            ],
        ),
        migrations.CreateModel(
            name='Teacher',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=50)),
            ],
        ),
        migrations.CreateModel(
            name='WeekDay',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('name', models.CharField(max_length=50)),
            ],
        ),
        migrations.CreateModel(
            name='TeacherSubject',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('subject', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Subject')),
                ('teacher', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Teacher')),
            ],
        ),
        migrations.CreateModel(
            name='SubjectRoomRestricted',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('room', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Room')),
                ('subject', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Subject')),
            ],
        ),
        migrations.CreateModel(
            name='RoomSubjectRestricted',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('room', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Room')),
                ('subject', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Subject')),
            ],
        ),
        migrations.CreateModel(
            name='LessonplanItem',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('class_id', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Class')),
                ('lesson_id', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Lesson')),
                ('lessonplan_id', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Lessonplan')),
                ('room_id', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Room')),
                ('subject_id', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Subject')),
                ('teacher_id', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Teacher')),
                ('weekday_id', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.WeekDay')),
            ],
        ),
        migrations.CreateModel(
            name='ClassSubject',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('count_in_week', models.IntegerField(default=1)),
                ('class_model', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Class')),
                ('subject', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lessonplans.Subject')),
            ],
        ),
    ]
