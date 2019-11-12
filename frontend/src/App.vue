<template>
  <v-app>
    <v-app-bar app dark color="primary">
      <v-toolbar-title>
        <span class="font-weight-medium">Example School</span>
      </v-toolbar-title>
      <v-spacer></v-spacer>
      <v-btn icon>
        <v-icon>mdi-magnify</v-icon>
      </v-btn>
    </v-app-bar>
    <v-content>
      <router-view />
    </v-content>
  </v-app>
</template>

<script>
import { mapActions } from "vuex";

export default {
  name: "app",
  methods: {
    ...mapActions(["getClasses", "getLessonplans"])
  },
  created() {
    this.getClasses();
    this.getLessonplans();
  }
};
</script>