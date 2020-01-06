<template>
  <div v-if="saveInProgress" class="loader-container">
    <v-progress-circular indeterminate color="#f5c21a"></v-progress-circular>
  </div>
  <div v-else>
    <lessonplan-creator-stepper :step-number="1"></lessonplan-creator-stepper>
    <div v-if="lessons.length > 0">
      <span class="list-header">Lessons</span>
      <v-list class="list-container">
        <v-list-item class="list-item" v-for="dataItem in lessons" :key="dataItem.id">
          {{ dataItem.name }}
          <v-btn
            text
            class="item-edit-btn"
            :to="`/example-school/management/lessons/edit/` + dataItem.id"
          >
            <v-icon>mdi-pencil</v-icon>
          </v-btn>
          <v-btn text class="item-delete-btn" @click="() => onDeleteClick(dataItem.id)">
            <v-icon>mdi-close</v-icon>
          </v-btn>
        </v-list-item>
      </v-list>
      <div class="list-empty-footer"></div>
      <v-btn
        fab
        dark
        color="#6d6d6d"
        class="btn-add-fab"
        :to="`/example-school/management/lessons/add`"
      >
        <v-icon>mdi-plus</v-icon>
      </v-btn>
    </div>
    <div v-else class="btn-container">
      <v-btn color="#6d6d6d" class="btn-add" :to="`/example-school/management/lessons/add`">Add</v-btn>
    </div>
    <back-next-bottom-bar :next-route="`/example-school/management/rooms`"></back-next-bottom-bar>
  </div>
</template>

<script>
import { mapState, mapActions } from 'vuex';
import BackNextBottomBar from '@/components/BackNextBottomBar';
import LessonplanCreatorStepper from '@/components/LessonplanCreatorStepper';

export default {
  name: 'add-lesson-list',
  components: { BackNextBottomBar, LessonplanCreatorStepper },
  computed: {
    ...mapState(['lessons', 'saveInProgress'])
  },
  methods: {
    ...mapActions(['deleteLesson']),
    onDeleteClick(dataId) {
      this.deleteLesson({ id: dataId });
    }
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
.list-container {
  margin: 0 0 70px 0;
}
.list-item {
  padding: 10px 20px;
}
.item-edit-btn {
  margin-left: auto;
  color: rgba(0, 0, 0, 0.5);
}
.item-delete-btn {
  color: rgba(0, 0, 0, 0.5);
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