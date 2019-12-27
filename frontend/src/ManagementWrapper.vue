<template>
  <v-app>
    <v-app-bar v-if="!customAppBar" app dark color="#f5c21a">
      <v-toolbar-title>
        <span class="font-weight-medium">Primary School Type</span>
      </v-toolbar-title>
      <v-spacer></v-spacer>
      <v-btn icon>
        <v-icon>mdi-magnify</v-icon>
      </v-btn>
    </v-app-bar>
    <v-content :class="whiteBackground ? `whiteBackground` : ``">
      <router-view></router-view>
    </v-content>
  </v-app>
</template>

<script>
import { mapActions } from 'vuex';

export default {
  name: 'management-wrapper',
  methods: {
    ...mapActions([
      'getSubjects',
      'getWeekdays',
      'getLessons',
      'getClasses',
      'getTeachers',
      'getRooms',
      'getLessonplans'
    ])
  },
  created() {
    this.getWeekdays();
    this.getLessons();
    this.getClasses();
    this.getSubjects();
    this.getTeachers();
    this.getRooms();
    this.getLessonplans();
  },
  computed: {
    customAppBar() {
      return this.$route.matched.some(
        match => match.props.default && match.props.default.customAppBar
      );
    },
    whiteBackground() {
      return this.$route.matched.some(
        match => match.props.default && match.props.default.whiteBackground
      );
    }
  }
};
</script>

<style scoped>
.whiteBackground {
  background: #fff;
}
</style>