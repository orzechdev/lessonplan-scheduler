<template>
  <div class="about">
    <v-breadcrumbs :items="items" divider=">"></v-breadcrumbs>
    <v-calendar
      ref="calendar"
      :now="todayDateString"
      :value="showedDateString"
      :first-interval="6"
      :interval-minutes="60"
      :interval-count="16"
      :interval-height="60"
      :event-overlap-threshold="50"
      :events="events"
      color="primary"
      type="week"
      :weekdays="[1, 2, 3, 4, 5]"
    ></v-calendar>
  </div>
</template>

<script>
import { mapState } from 'vuex';

export default {
  name: 'timetableteacher',
  props: {
    classId: String
  },
  computed: {
    ...mapState(['teachers', 'lessonplans']),
    classes() {
      return this.teachers ? this.teachers : [];
    },
    currentClass() {
      return this.classes.find(elem => elem.id == this.classId);
    },
    items() {
      const classItem = this.currentClass;
      const className = classItem ? classItem.name : '';

      return [
        {
          text: 'Lessonplans',
          disabled: false,
          to: '/example-school/lessonplans',
          exact: true
        },
        {
          text: className
        }
      ];
    },
    todayDate() {
      return new Date();
    },
    todayDateString() {
      return `${this.todayDate.getFullYear()}-${this.todayDate.getMonth() +
        1}-${this.todayDate.getDate()}`;
    },
    showedDate() {
      const showedDate = new Date();
      const startDay = showedDate.getDay();

      if (startDay === 6) {
        // Change saturday to monday next week
        showedDate.setDate(showedDate.getDate() + 2);
      } else if (startDay === 0) {
        // Change sunday to monday next week
        showedDate.setDate(showedDate.getDate() + 1);
      }

      return showedDate;
    },
    showedDateString() {
      return `${this.showedDate.getFullYear()}-${this.showedDate.getMonth() +
        1}-${this.showedDate.getDate()}`;
    },
    events() {
      const classItem = this.currentClass;

      if (classItem && this.lessonplans) {
        const mondayDate = new Date();
        const todayDay = mondayDate.getDay();

        if (todayDay === 6) {
          // Change saturday to monday next week
          mondayDate.setDate(mondayDate.getDate() + 2);
        } else if (todayDay === 0) {
          // Change sunday to monday next week
          mondayDate.setDate(mondayDate.getDate() + 1);
        } else {
          // Change any week day to monday current week
          mondayDate.setDate(mondayDate.getDate() - (todayDay - 1));
        }

        const eventsList = this.lessonplans
          .filter(({ teacher: classModel }) => classModel.id === classItem.id)
          .map(({ weekday, lesson, subject, classModel }) => {
            const lessonWeekDay = Number(weekday.name) - 1;

            const startTimes = lesson.startTime.split(':');
            const endTimes = lesson.endTime.split(':');

            const lessonCurrentDate = new Date(mondayDate.getTime());
            lessonCurrentDate.setDate(mondayDate.getDate() + lessonWeekDay);
            const lessonCurrentDateString = `${lessonCurrentDate.getFullYear()}-${lessonCurrentDate.getMonth() +
              1}-${lessonCurrentDate.getDate()}`;

            return {
              start: `${lessonCurrentDateString} ${startTimes[0]}:${startTimes[1]}`,
              end: `${lessonCurrentDateString} ${endTimes[0]}:${endTimes[1]}`,
              name: subject.name + ', ' + classModel.name
            };
          });

        return eventsList;
      } else {
        return [];
      }
    }
  }
};
</script>
