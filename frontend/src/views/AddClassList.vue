<template>
  <div v-if="saveInProgress" class="loader-container">
    <v-progress-circular indeterminate color="#f5c21a"></v-progress-circular>
  </div>
  <div v-else>
    <lessonplan-creator-stepper :step-number="5"></lessonplan-creator-stepper>
    <div v-if="classes.length > 0">
      <span class="list-header">Classes</span>
      <v-list class="list-container">
        <v-list-item
          class="list-item"
          v-for="dataItem in classes"
          :key="dataItem.id"
          :to="`/example-school/lessonplans/` + dataItem.id"
        >{{ dataItem.name }}</v-list-item>
      </v-list>
      <v-btn
        fab
        dark
        color="#6d6d6d"
        class="btn-add-fab"
        :to="`/example-school/management/classes/add`"
      >
        <v-icon>mdi-plus</v-icon>
      </v-btn>
    </div>
    <div v-else class="btn-container">
      <v-btn color="#6d6d6d" class="btn-add" :to="`/example-school/management/classes/add`">Add</v-btn>
    </div>
    <back-next-bottom-bar
      :back-route="`/example-school/management/teachers`"
      :next-route="`/example-school/management/generate`"
    ></back-next-bottom-bar>
  </div>
</template>

<script>
import { mapState } from 'vuex';
import BackNextBottomBar from '@/components/BackNextBottomBar';
import LessonplanCreatorStepper from '@/components/LessonplanCreatorStepper';

export default {
  name: 'add-class-list',
  components: { BackNextBottomBar, LessonplanCreatorStepper },
  computed: {
    ...mapState(['classes', 'saveInProgress'])
  }
};
</script>

<style scoped>
.loader-container {
  display: flex;
  justify-content: center;
  padding: 35% 0;
}
.list-header {
  display: inline-block;
  width: 100%;
  padding: 10px 20px;
  background: #fff;
  color: #6d6d6d;
}
.list-item {
  padding: 10px 20px;
}
.list-container {
  margin: 0 0 70px 0;
}
.btn-container {
  display: flex;
  justify-content: center;
  padding: 35% 0;
}
.btn-add {
  color: #fff;
}
.btn-add-fab {
  position: fixed;
  bottom: 90px;
  right: 20px;
}
</style>