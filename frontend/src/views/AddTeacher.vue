<template>
  <div>
    <v-app-bar app color="#fff">
      <v-btn icon to="/example-school/management/teachers" color="#fff">
        <v-icon color="#777">mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>
        <span class="font-weight-medium">Add teacher</span>
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
    <add-next-bottom-bar @addClick="onAddClick" @addNextClick="onAddNextClick"></add-next-bottom-bar>
  </div>
</template>

<script>
import { mapState, mapActions } from 'vuex';
import FormContainer from '@/components/FormContainer';
import AddNextBottomBar from '@/components/AddNextBottomBar';

export default {
  name: 'add-teacher',
  components: { FormContainer, AddNextBottomBar },
  computed: {
    ...mapState(['saveInProgress', 'subjects'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ],
    nameAndSurname: '',
    teachedSubjects: []
  }),
  methods: {
    ...mapActions(['createTeacher']),
    onAddClick() {
      console.log('onAddClick TODO: add/mutate also teacher subjects');
      // this.createTeacher({
      //   fullName: this.nameAndSurname
      // });
      // this.$router.push('/example-school/management/teachers');
    },
    onAddNextClick() {
      console.log('onAddNextClick');
    }
  }
};
</script>
