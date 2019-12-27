<template>
  <v-stepper :value="stepNumber" class="stepper">
    <v-stepper-header>
      <v-stepper-step :complete="stepNumber > 1" step="1" color="#f5c21a">Add lessons</v-stepper-step>

      <v-divider></v-divider>

      <v-stepper-step :complete="stepNumber > 2" step="2" color="#f5c21a">Add rooms</v-stepper-step>

      <v-divider></v-divider>

      <v-stepper-step :complete="stepNumber > 3" step="3" color="#f5c21a">Add subjects</v-stepper-step>

      <v-divider></v-divider>

      <v-stepper-step :complete="stepNumber > 4" step="4" color="#f5c21a">Add teachers</v-stepper-step>

      <v-divider></v-divider>

      <v-stepper-step :complete="stepNumber > 5" step="5" color="#f5c21a">Add classes</v-stepper-step>
    </v-stepper-header>
  </v-stepper>
</template>

<script>
export default {
  name: 'lessonplan-creator-stepper',
  props: ['stepNumber']
};
</script>

<style scoped>
.stepper {
  background: #fff;
  box-shadow: none;
}
</style>