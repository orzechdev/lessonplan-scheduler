<template>
  <div class="about">
    <v-breadcrumbs :items="items" divider=">"></v-breadcrumbs>
    <v-calendar
      ref="calendar"
      :now="today"
      :value="today"
      :events="events"
      color="primary"
      type="week"
    ></v-calendar>
  </div>
</template>

<script>
import { mapState, mapActions } from "vuex";

export default {
  name: "timetable",
  props: {
    classId: String
  },
  computed: {
    ...mapState(["classes"]),
    items() {
      const classItem = this.classes.find(elem => elem.id == this.classId)
      const className = classItem ? classItem.name : ''
      
      return [
        {
          text: "Lessonplans",
          disabled: false,
          to: "/example-school/lessonplans",
          exact: true
        },
        {
          text: className
        }
      ];
    }
  },
  data() {
    return {
      today: "2019-01-08",
      events: [
        {
          name: "Weekly Meeting",
          start: "2019-01-07 09:00",
          end: "2019-01-07 10:00"
        },
        {
          name: "Thomas' Birthday",
          start: "2019-01-10"
        },
        {
          name: "Mash Potatoes",
          start: "2019-01-09 12:30",
          end: "2019-01-09 15:30"
        }
      ]
    };
  }
};
</script>