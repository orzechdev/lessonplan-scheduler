<template>
  <div class="bottom-bar">
    <v-btn v-if="onAddClick" dark color="#f5c21a" class="btn btn-add" @click="onAddClick">Add</v-btn>
    <v-btn
      v-if="onAddNextClick"
      dark
      color="#f5c21a"
      class="btn btn-add-next"
      @click="onAddNextClick"
    >Add and next</v-btn>
  </div>
</template>

<script>
import { mapState } from 'vuex';

export default {
  name: 'add-next-bottom-bar',
  computed: {
    ...mapState(['classes'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ]
  }),
  methods: {
    onAddClick() {
      this.$emit('addClick');
    },
    onAddNextClick() {
      this.$emit('addNextClick');
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