<template>
  <div class="bottom-bar">
    <v-btn
      v-if="onDeleteClick"
      dark
      color="#f55050"
      class="btn btn-delete"
      @click="onDeleteClick"
    >Delete</v-btn>
    <v-btn v-if="onSaveClick" dark color="#f5c21a" class="btn btn-save" @click="onSaveClick">Save</v-btn>
  </div>
</template>

<script>
import { mapState } from 'vuex';

export default {
  name: 'save-delete-bottom-bar',
  methods: {
    onSaveClick() {
      this.$emit('saveClick');
    },
    onDeleteClick() {
      this.$emit('deleteClick');
    }
  }
};
</script>

<style scoped>
.bottom-bar {
  width: 100%;
  height: 70px;
  background: #fff;
  box-shadow: 0px 2px 4px -1px rgba(0, 0, 0, 0.2), 0px 4px 5px 0px rgba(0, 0, 0, 0.14),
    0px 1px 10px 0px rgba(0, 0, 0, 0.12);
  position: fixed;
  bottom: 0;
  display: flex;
  align-items: center;
  justify-content: flex-end;
  flex-direction: row;
  padding: 0 20px;
}
.btn {
  margin: 0 0 0 20px;
}
</style>