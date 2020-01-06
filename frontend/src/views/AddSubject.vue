<template>
  <div>
    <v-app-bar app color="#fff">
      <v-btn icon to="/example-school/management/subjects" color="#fff">
        <v-icon color="#777">mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>
        <span class="font-weight-medium">{{dataId ? `Edit subject` : `Add subject`}}</span>
      </v-toolbar-title>
    </v-app-bar>
    <form-container>
      <v-text-field v-model="subjectName" label="Subject name" outlined color="#f5c21a"></v-text-field>
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
  name: 'add-subject',
  components: { FormContainer, AddNextBottomBar, SaveDeleteBottomBar },
  computed: {
    ...mapState(['subjects'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ],
    subjectName: '',
    dataId: undefined
  }),
  methods: {
    ...mapActions(['createSubject', 'updateSubject', 'deleteSubject']),
    initData(paramDataId, subjects) {
      if (paramDataId && !this.dataId && subjects && subjects.length) {
        const data = subjects.find(dataItem => dataItem.id === paramDataId);
        if (data) {
          this.subjectName = data.name;
          this.dataId = paramDataId;
        }
      }
    },
    onAddClick() {
      this.createSubject({
        subjectName: this.subjectName
      });
      this.$router.push('/example-school/management/subjects');
    },
    onAddNextClick() {
      this.createSubject({
        subjectName: this.subjectName
      });
      this.subjectName = '';
    },
    onSaveClick() {
      this.updateSubject({
        id: this.dataId,
        subjectName: this.subjectName
      });
      this.$router.push('/example-school/management/subjects');
    },
    onDeleteClick() {
      this.deleteSubject({ id: this.$route.params.dataId });
      this.$router.push('/example-school/management/subjects');
    }
  },
  watch: {
    subjects(subjects) {
      this.initData(this.$route.params.dataId, subjects);
    }
  },
  mounted() {
    this.initData(this.$route.params.dataId, this.subjects);
  }
};
</script>
