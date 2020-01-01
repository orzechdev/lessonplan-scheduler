<template>
  <div v-if="!generationInProgress" class="container">
    <div class="container-small">
      <h3 class="title">Setup finished!</h3>
      <p class="description">Everything is setup. Now you can proceed and generate all lesson plans.</p>
      <v-btn dark color="#f5c21a" class="btn btn-generate" @click="onGenerateClick">Generate</v-btn>
    </div>
    <back-next-bottom-bar :back-route="`/example-school/management/classes`"></back-next-bottom-bar>
  </div>
  <div v-else-if="generationInProgress" class="container">
    <div class="container-small">
      <h3 class="title">Generating lesson plans</h3>
      <v-progress-linear v-model="generationProgressValue" color="#f5c21a"></v-progress-linear>
    </div>
  </div>
</template>

<script>
import { mapState, mapActions } from 'vuex';
import BackNextBottomBar from '@/components/BackNextBottomBar';

export default {
  name: 'generate',
  components: { BackNextBottomBar },
  computed: {
    ...mapState(['saveInProgress', 'subjects'])
  },
  data: () => ({
    generationInProgress: false,
    generationProgressValue: 0,
    generationProgressValueInterval: 0,
    generationFinish: false,
    generationError: false
  }),
  watch: {
    generationProgressValue(val) {
      if (val < 100) return;

      clearInterval(this.generationProgressValueInterval);
    }
  },
  methods: {
    ...mapActions(['createClass']),
    onGenerateClick() {
      this.generationInProgress = true;
      clearInterval(this.generationProgressValueInterval);

      this.generationProgressValueInterval = setInterval(() => {
        this.generationProgressValue += 300 / 60; //Math.random() * (15 - 5) + 5;
      }, 3000);
    }
  }
};
</script>

<style scoped>
.container {
  display: flex;
  align-items: center;
  justify-content: center;
}
.container-small {
  margin: 35vh 0 0 0;
  width: 300px;
  text-align: center;
}
.title {
  margin: 0 0 20px 0;
  color: rgba(0, 0, 0, 0.87);
}
.description {
  margin: 0 0 25px 0;
  color: #6d6d6d;
}
</style>