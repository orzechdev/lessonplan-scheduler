<template>
  <div>
    <v-app-bar app color="#fff">
      <v-btn icon to="/example-school/management/teachers" color="#fff">
        <v-icon color="#777">mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>
        <span class="font-weight-medium">{{dataId ? `Edit teacher` : `Add teacher`}}</span>
      </v-toolbar-title>
    </v-app-bar>
    <form-container>
      <v-text-field v-model="nameAndSurname" label="Name and surname" outlined color="#f5c21a"></v-text-field>
      <v-combobox
        v-model="teachedSubjects"
        :items="subjects"
        item-text="name"
        item-value="id"
        label="Subjects"
        multiple
        outlined
        color="#f5c21a"
        item-color="#f5c21a"
      ></v-combobox>
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
  name: 'add-teacher',
  components: { FormContainer, AddNextBottomBar, SaveDeleteBottomBar },
  computed: {
    ...mapState(['teachers', 'subjects'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ],
    nameAndSurname: '',
    teachedSubjects: [],
    dataId: undefined
  }),
  methods: {
    ...mapActions(['createTeacher', 'updateTeacher', 'deleteTeacher']),
    initData(paramDataId, teachers) {
      if (paramDataId && !this.dataId && teachers && teachers.length) {
        const data = teachers.find(dataItem => dataItem.id === paramDataId);
        if (data) {
          this.nameAndSurname = data.name;
          this.teachedSubjects = data.teachersubjectSet.map(subjectSet => subjectSet.subject);
          this.dataId = paramDataId;
        }
      }
    },
    onAddClick() {
      this.createTeacher({
        fullName: this.nameAndSurname,
        subjectsIds: this.teachedSubjects.map(({ id }) => id)
      });
      this.$router.push('/example-school/management/teachers');
    },
    onAddNextClick() {
      this.createTeacher({
        fullName: this.nameAndSurname,
        subjectsIds: this.teachedSubjects.map(({ id }) => id)
      });
      this.nameAndSurname = '';
      this.teachedSubjects = [];
    },
    onSaveClick() {
      this.updateTeacher({
        id: this.dataId,
        fullName: this.nameAndSurname,
        subjectsIds: this.teachedSubjects.map(({ id }) => id)
      });
      this.$router.push('/example-school/management/teachers');
    },
    onDeleteClick() {
      this.deleteTeacher({ id: this.$route.params.dataId });
      this.$router.push('/example-school/management/teachers');
    }
  },
  watch: {
    teachers(teachers) {
      this.initData(this.$route.params.dataId, teachers);
    }
  },
  mounted() {
    this.initData(this.$route.params.dataId, this.teachers);
  }
};
</script>
