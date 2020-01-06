<template>
  <div>
    <v-app-bar app color="#fff">
      <v-btn icon to="/example-school/management/classes" color="#fff">
        <v-icon color="#777">mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>
        <span class="font-weight-medium">{{dataId ? `Edit class` : `Add class`}}</span>
      </v-toolbar-title>
    </v-app-bar>
    <form-container>
      <v-text-field v-model="className" label="Class name" outlined color="#f5c21a"></v-text-field>
      <div class="subjects-list-header">
        <span class="subjects-list-header-col-left">Subjects</span>
        <span class="subjects-list-header-col-right">Hours per week</span>
      </div>
      <v-list class="subjects-list-container">
        <v-list-item
          class="subjects-list-item"
          v-for="(classSubjectWithHours, classSubjectWithHoursIndex) in classSubjectsWithHoursPerWeek"
          :key="classSubjectWithHours.subject.id"
        >
          <span class="subjects-list-item-col-left">{{ classSubjectWithHours.subject.name }}</span>
          <span class="subjects-list-header-col-right">{{ classSubjectWithHours.hoursPerWeek }}</span>
          <span class="subjects-list-item-col-right-icon-btn-container">
            <v-btn
              icon
              class="subjects-list-item-col-right-icon-btn"
              dark
              @click="hoursSelectorDialogDataIndex = classSubjectWithHoursIndex; hoursPerWeekInDialog = classSubjectWithHours.hoursPerWeek"
              @click.stop="hoursSelectorDialog = true"
            >
              <v-icon color="#777">mdi-pencil</v-icon>
            </v-btn>
          </span>
        </v-list-item>
      </v-list>
      <v-dialog
        v-if="hoursSelectorDialogDataIndex != null"
        v-model="hoursSelectorDialog"
        persistent
        max-width="600px"
      >
        <v-card>
          <v-card-title>
            <span
              class="headline"
            >{{ classSubjectsWithHoursPerWeek[hoursSelectorDialogDataIndex].subject.name }}</span>
          </v-card-title>
          <v-card-text v-if="showDialogFileds" class="subject-hours-edit-dialog-content">
            <v-text-field
              v-model="hoursPerWeekInDialog"
              label="Hours per week"
              outlined
              color="#f5c21a"
            ></v-text-field>
          </v-card-text>
          <v-card-actions>
            <v-spacer></v-spacer>
            <v-btn color="#f5c21a" text @click="hoursSelectorDialog = false">Close</v-btn>
            <v-btn
              color="#f5c21a"
              text
              @click="classSubjectsWithHoursPerWeek[hoursSelectorDialogDataIndex].hoursPerWeek = hoursPerWeekInDialog; hoursSelectorDialog = false"
            >Save</v-btn>
          </v-card-actions>
        </v-card>
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
  name: 'add-class',
  components: { FormContainer, AddNextBottomBar, SaveDeleteBottomBar },
  computed: {
    ...mapState(['saveInProgress', 'classes', 'subjects'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ],
    className: '',
    classSubjectsWithHoursPerWeek: [],
    classSubjectsWithHoursPerWeekAlreadySet: false,
    hoursPerWeekInDialog: 0,
    hoursSelectorDialog: false,
    hoursSelectorDialogDataIndex: null,
    showDialogFileds: false,
    dataId: undefined
  }),
  methods: {
    ...mapActions(['createClass', 'updateClass', 'deleteClass']),
    initData(paramDataId, classes, subjects) {
      if (
        paramDataId &&
        !this.dataId &&
        classes &&
        classes.length &&
        subjects &&
        subjects.length &&
        this.classSubjectsWithHoursPerWeekAlreadySet
      ) {
        const data = classes.find(dataItem => dataItem.id === paramDataId);
        if (data) {
          this.className = data.name;
          this.classSubjectsWithHoursPerWeek = this.classSubjectsWithHoursPerWeek.map(
            ({ subject, hoursPerWeek }) => {
              const classSubject = data.classsubjectSet.find(
                classSubject => classSubject.subject.id == subject.id
              );
              return {
                subject,
                hoursPerWeek: classSubject ? classSubject.countInWeek : hoursPerWeek
              };
            }
          );
          this.dataId = paramDataId;
        }
      }
    },
    onAddClick() {
      this.createClass({
        className: this.className,
        subjectsData: this.classSubjectsWithHoursPerWeek
          .filter(({ hoursPerWeek }) => hoursPerWeek >= 1)
          .map(({ subject, hoursPerWeek }) => ({ id: subject.id, countInWeek: hoursPerWeek }))
      });
      this.$router.push('/example-school/management/classes');
    },
    onAddNextClick() {
      this.createClass({
        className: this.className,
        subjectsData: this.classSubjectsWithHoursPerWeek
          .filter(({ hoursPerWeek }) => hoursPerWeek >= 1)
          .map(({ subject, hoursPerWeek }) => ({ id: subject.id, countInWeek: hoursPerWeek }))
      });
      this.className = '';
      this.classSubjectsWithHoursPerWeek = this.subjects.map(subject => ({
        subject,
        hoursPerWeek: 0
      }));
    },
    onSaveClick() {
      this.updateClass({
        id: this.dataId,
        className: this.className,
        subjectsData: this.classSubjectsWithHoursPerWeek
          .filter(({ hoursPerWeek }) => hoursPerWeek >= 1)
          .map(({ subject, hoursPerWeek }) => ({ id: subject.id, countInWeek: hoursPerWeek }))
      });
      this.$router.push('/example-school/management/classes');
    },
    onDeleteClick() {
      this.deleteClass({ id: this.$route.params.dataId });
      this.$router.push('/example-school/management/classes');
    }
  },
  watch: {
    classes(classes) {
      this.initData(this.$route.params.dataId, classes, this.subjects);
    },
    subjects(subjects) {
      if (
        this.classSubjectsWithHoursPerWeek.length <= 0 &&
        !this.classSubjectsWithHoursPerWeekAlreadySet
      ) {
        this.classSubjectsWithHoursPerWeek = subjects.map(subject => ({
          subject,
          hoursPerWeek: 0
        }));
        this.classSubjectsWithHoursPerWeekAlreadySet = true;
      }
      this.initData(this.$route.params.dataId, this.classes, subjects);
    },
    hoursSelectorDialog: function(newHoursSelectorDialog) {
      setTimeout(() => {
        this.showDialogFileds = newHoursSelectorDialog;
      }, 100);
    }
  },
  mounted() {
    if (
      this.subjects &&
      this.subjects.length > 0 &&
      this.classSubjectsWithHoursPerWeek.length <= 0 &&
      !this.classSubjectsWithHoursPerWeekAlreadySet
    ) {
      this.classSubjectsWithHoursPerWeek = this.subjects.map(subject => ({
        subject,
        hoursPerWeek: 0
      }));
      this.classSubjectsWithHoursPerWeekAlreadySet = true;
    }
    this.initData(this.$route.params.dataId, this.classes, this.subjects);
  }
};
</script>

<style scoped>
.subjects-list-header {
  display: flex;
  width: 100%;
  background: #fff;
  color: #6d6d6d;
}
.subjects-list-container {
  margin: 0 0 90px 0;
}
.subjects-list-item {
  display: flex;
  padding: 0;
}
.subjects-list-header-col-left,
.subjects-list-item-col-left {
  width: 60%;
}
.subjects-list-header-col-right,
.subjects-list-item-col-right {
  width: 30%;
}
.subjects-list-item-col-right-icon-btn-container {
  width: 10%;
}
.subjects-list-item-col-right-icon-btn {
  float: right;
}
.subject-hours-edit-dialog-content {
  padding: 20px 24px 10px 24px !important;
}
</style>