<template>
  <div>
    <v-app-bar app color="#fff">
      <v-btn icon to="/example-school/management/rooms" color="#fff">
        <v-icon color="#777">mdi-close</v-icon>
      </v-btn>
      <v-toolbar-title>
        <span class="font-weight-medium">{{dataId ? `Edit room` : `Add room`}}</span>
      </v-toolbar-title>
    </v-app-bar>
    <form-container>
      <v-text-field v-model="roomName" label="Room name" outlined color="#f5c21a"></v-text-field>
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
  name: 'add-room',
  components: { FormContainer, AddNextBottomBar, SaveDeleteBottomBar },
  computed: {
    ...mapState(['rooms'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ],
    roomName: '',
    dataId: undefined
  }),
  methods: {
    ...mapActions(['createRoom', 'updateRoom', 'deleteRoom']),
    initData(paramDataId, rooms) {
      if (paramDataId && !this.dataId && rooms && rooms.length) {
        const data = rooms.find(dataItem => dataItem.id === paramDataId);
        if (data) {
          this.roomName = data.name;
          this.dataId = paramDataId;
        }
      }
    },
    onAddClick() {
      this.createRoom({
        roomName: this.roomName
      });
      this.$router.push('/example-school/management/rooms');
    },
    onAddNextClick() {
      this.createRoom({
        roomName: this.roomName
      });
      this.roomName = '';
    },
    onSaveClick() {
      this.updateRoom({
        id: this.dataId,
        roomName: this.roomName
      });
      this.$router.push('/example-school/management/rooms');
    },
    onDeleteClick() {
      this.deleteRoom({ id: this.$route.params.dataId });
      this.$router.push('/example-school/management/rooms');
    }
  },
  watch: {
    rooms(rooms) {
      this.initData(this.$route.params.dataId, rooms);
    }
  },
  mounted() {
    this.initData(this.$route.params.dataId, this.rooms);
  }
};
</script>
