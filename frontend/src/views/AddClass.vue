<template>
  <div>
    <v-app-bar app color="#fff">
      <v-btn icon to="/example-school/management/classes" color="#fff">
        <v-icon color="#777">mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>
        <span class="font-weight-medium">Add class</span>
      </v-toolbar-title>
    </v-app-bar>
    <form-container>
      <v-text-field v-model="className" label="Class name" outlined color="#f5c21a"></v-text-field>
    </form-container>
    <add-next-bottom-bar @addClick="onAddClick" @addNextClick="onAddNextClick"></add-next-bottom-bar>
  </div>
</template>

<script>
import { mapState, mapActions } from 'vuex';
import FormContainer from '@/components/FormContainer';
import AddNextBottomBar from '@/components/AddNextBottomBar';

export default {
  name: 'add-class',
  components: { FormContainer, AddNextBottomBar },
  computed: {
    ...mapState(['saveInProgress'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ],
    className: ''
  }),
  methods: {
    onAddClick() {
      console.log('onAddClick');
      // this.$router.push('/example-school/management/classes');
    },
    onAddNextClick() {
      console.log('onAddNextClick');
    }
  }
};
</script>
