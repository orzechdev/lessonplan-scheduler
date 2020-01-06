<template>
  <div v-if="saveInProgress" class="loader-container">
    <v-progress-circular indeterminate color="#f5c21a"></v-progress-circular>
  </div>
  <div v-else>
    <lessonplan-creator-stepper :step-number="3"></lessonplan-creator-stepper>
    <div v-if="subjects.length > 0">
      <span class="list-header">Subjects</span>
      <v-list class="list-container">
        <v-list-item class="list-item" v-for="dataItem in subjects" :key="dataItem.id">
          {{ dataItem.name }}
          <v-btn
            text
            class="item-edit-btn"
            :to="`/example-school/management/subjects/edit/` + dataItem.id"
          >
            <v-icon>mdi-pencil</v-icon>
          </v-btn>
          <v-btn text class="item-delete-btn" @click="() => onDeleteClick(dataItem.id)">
            <v-icon>mdi-close</v-icon>
          </v-btn>
        </v-list-item>
      </v-list>
      <v-btn
        fab
        dark
        color="#6d6d6d"
        class="btn-add-fab"
        :to="`/example-school/management/subjects/add`"
      >
        <v-icon>mdi-plus</v-icon>
      </v-btn>
    </div>
    <div v-else class="btn-container">
      <v-btn color="#6d6d6d" class="btn-add" :to="`/example-school/management/subjects/add`">Add</v-btn>
    </div>
    <back-next-bottom-bar
      :back-route="`/example-school/management/rooms`"
      :next-route="`/example-school/management/teachers`"
    ></back-next-bottom-bar>
  </div>
</template>

<script>
import { mapState, mapActions } from 'vuex';
import BackNextBottomBar from '@/components/BackNextBottomBar';
import LessonplanCreatorStepper from '@/components/LessonplanCreatorStepper';

export default {
  name: 'add-subject-list',
  components: { BackNextBottomBar, LessonplanCreatorStepper },
  computed: {
    ...mapState(['subjects', 'saveInProgress'])
  },
  methods: {
    ...mapActions(['deleteSubject']),
    onDeleteClick(dataId) {
      this.deleteSubject({ id: dataId });
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