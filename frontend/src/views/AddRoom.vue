<template>
  <div>
    <v-app-bar app color="#fff">
      <v-btn icon to="/example-school/management/rooms" color="#fff">
        <v-icon color="#777">mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>
        <span class="font-weight-medium">Add room</span>
      </v-toolbar-title>
    </v-app-bar>
    <form-container>
      <v-text-field v-model="roomName" label="Room name" outlined color="#f5c21a"></v-text-field>
    </form-container>
    <add-next-bottom-bar @addClick="onAddClick" @addNextClick="onAddNextClick"></add-next-bottom-bar>
  </div>
</template>

<script>
import { mapState, mapActions } from 'vuex';
import FormContainer from '@/components/FormContainer';
import AddNextBottomBar from '@/components/AddNextBottomBar';

export default {
  name: 'add-room',
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
    roomName: ''
  }),
  methods: {
    ...mapActions(['createRoom']),
    onAddClick() {
      this.createRoom({
        roomName: this.roomName
      });
      this.$router.push('/example-school/management/rooms');
    },
    onAddNextClick() {
      console.log('onAddNextClick');
    }
  }
};
</script>
