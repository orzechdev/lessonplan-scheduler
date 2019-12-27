<template>
  <div class="bottom-bar">
    <div class="btn-container">
      <v-btn
        v-if="backRoute"
        dark
        color="#f5c21a"
        outlined
        class="btn btn-back"
        :to="backRoute"
      >Back</v-btn>
      <v-btn v-if="nextRoute" dark color="#f5c21a" class="btn btn-next" :to="nextRoute">Next</v-btn>
    </div>
  </div>
</template>

<script>
import { mapState } from 'vuex';

export default {
  name: 'back-next-bottom-bar',
  props: ['backRoute', 'nextRoute'],
  computed: {
    ...mapState(['classes'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ]
  })
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
  padding: 0 20px;
  display: flex;
  align-items: center;
}
.btn-container {
  width: 100%;
}
.btn-back {
  float: left;
}
.btn-next {
  float: right;
}
</style>