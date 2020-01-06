<template>
  <div>
    <v-app-bar app color="#fff">
      <v-btn icon to="/example-school/management/lessons" color="#fff">
        <v-icon color="#777">mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>
        <span class="font-weight-medium">{{dataId ? `Edit lesson` : `Add lesson`}}</span>
      </v-toolbar-title>
    </v-app-bar>
    <form-container>
      <v-text-field v-model="lessonNumber" label="Lesson number" outlined color="#f5c21a"></v-text-field>
      <v-dialog
        ref="dialogStartTime"
        v-model="startTimeModal"
        :return-value.sync="startTime"
        persistent
        width="290px"
      >
        <template v-slot:activator="startTimeScope">
          <v-text-field
            v-model="startTime"
            outlined
            color="#f5c21a"
            label="Start time"
            readonly
            v-on="startTimeScope.on"
          ></v-text-field>
        </template>
        <v-time-picker
          v-if="startTimeModal"
          v-model="startTime"
          format="24hr"
          full-width
          color="#f5c21a"
        >
          <v-spacer></v-spacer>
          <v-btn text color="#f5c21a" @click="startTimeModal = false">Cancel</v-btn>
          <v-btn text color="#f5c21a" @click="$refs.dialogStartTime.save(startTime)">OK</v-btn>
        </v-time-picker>
      </v-dialog>
      <v-dialog
        ref="dialogEndTime"
        v-model="endTimeModal"
        :return-value.sync="endTime"
        persistent
        width="290px"
      >
        <template v-slot:activator="endTimeScope">
          <v-text-field
            v-model="endTime"
            outlined
            color="#f5c21a"
            label="End time"
            readonly
            v-on="endTimeScope.on"
          ></v-text-field>
        </template>
        <v-time-picker
          v-if="endTimeModal"
          v-model="endTime"
          format="24hr"
          full-width
          color="#f5c21a"
        >
          <v-spacer></v-spacer>
          <v-btn text color="#f5c21a" @click="endTimeModal = false">Cancel</v-btn>
          <v-btn text color="#f5c21a" @click="$refs.dialogEndTime.save(endTime)">OK</v-btn>
        </v-time-picker>
      </v-dialog>
    </form-container>
    <save-delete-bottom-bar v-if="dataId" @saveClick="onSaveClick" @deleteClick="onDeleteClick"></save-delete-bottom-bar>
    <add-next-bottom-bar v-else @addClick="onAddClick" @addNextClick="onAddNextClick"></add-next-bottom-bar>
  </div>
</template>

<script>
import { mapState, mapActions } from 'vuex';
import FormContainer from '@/components/FormContainer';
import AddNextBottomBar from '@/components/AddNextBottomBar';
import SaveDeleteBottomBar from '@/components/SaveDeleteBottomBar';

export default {
  name: 'add-lesson',
  components: { FormContainer, AddNextBottomBar, SaveDeleteBottomBar },
  computed: {
    ...mapState(['lessons'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ],
    lessonNumber: '',
    startTime: null,
    startTimeModal: false,
    endTime: null,
    endTimeModal: false,
    dataId: undefined
  }),
  methods: {
    ...mapActions(['createLesson', 'updateLesson', 'deleteLesson']),
    initData(paramDataId, lessons) {
      if (paramDataId && !this.dataId && lessons && lessons.length) {
        const data = lessons.find(dataItem => dataItem.id === paramDataId);
        if (data) {
          this.lessonNumber = data.name;
          this.startTime = data.startTime;
          this.endTime = data.endTime;
          this.dataId = paramDataId;
        }
      }
    },
    onAddClick() {
      this.createLesson({
        lessonNumber: this.lessonNumber,
        startTime: this.startTime,
        endTime: this.endTime
      });
      this.$router.push('/example-school/management/lessons');
    },
    onAddNextClick() {
      this.createLesson({
        lessonNumber: this.lessonNumber,
        startTime: this.startTime,
        endTime: this.endTime
      });
      this.lessonNumber = '';
      this.startTime = null;
      this.endTime = null;
    },
    onSaveClick() {
      this.updateLesson({
        id: this.dataId,
        lessonNumber: this.lessonNumber,
        startTime: this.startTime,
        endTime: this.endTime
      });
      this.$router.push('/example-school/management/lessons');
    },
    onDeleteClick() {
      this.deleteLesson({ id: this.$route.params.dataId });
      this.$router.push('/example-school/management/lessons');
    }
  },
  watch: {
    lessons(lessons) {
      this.initData(this.$route.params.dataId, lessons);
    }
  },
  mounted() {
    this.initData(this.$route.params.dataId, this.lessons);
  }
};
</script>
