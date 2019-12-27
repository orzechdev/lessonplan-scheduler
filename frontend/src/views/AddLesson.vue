<template>
  <div>
    <v-app-bar app color="#fff">
      <v-btn icon to="/example-school/management/lessons" color="#fff">
        <v-icon color="#777">mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>
        <span class="font-weight-medium">Add lesson</span>
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
    <add-next-bottom-bar @addClick="onAddClick" @addNextClick="onAddNextClick"></add-next-bottom-bar>
  </div>
</template>

<script>
import { mapState, mapActions } from 'vuex';
import FormContainer from '@/components/FormContainer';
import AddNextBottomBar from '@/components/AddNextBottomBar';

export default {
  name: 'add-lesson',
  components: { FormContainer, AddNextBottomBar },
  computed: {
    ...mapState([])
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
    endTimeModal: false
  }),
  methods: {
    ...mapActions(['createLesson']),
    onAddClick() {
      this.createLesson({
        lessonNumber: this.lessonNumber,
        startTime: this.startTime,
        endTime: this.endTime
      });
      this.$router.push('/example-school/management/lessons');
    },
    onAddNextClick() {
      console.log('onAddNextClick');
    }
  }
};
</script>
