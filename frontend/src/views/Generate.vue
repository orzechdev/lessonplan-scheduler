<template>
  <div v-if="!generationInProgress && !generationFinish && !generationError" class="container">
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
  <div v-else-if="generationFinish" class="container">
    <div>
      <div class="max-width">
        <div class="container-medium">
          <h3 class="title">Generating lesson plans finished</h3>
          <p
            v-if="hardScoresFailed"
            class="description"
          >Unfortunatelly, generated lesson plans are not acceptable. You can try to change inserted data or try to generate again.</p>
          <p
            v-else-if="softScoresFailed"
            class="description"
          >Generated lesson plans are not fully optimal, although are acceptable.</p>
          <p v-else class="description">Generated lesson plans are optimal and acceptable.</p>
        </div>
      </div>
      <div class="max-width">
        <div
          v-if="generationData && generationData.lessonplanHardScores && generationData.lessonplanHardScores.length"
        >
          <h4 class="subtitle">Unacceptable errors</h4>
          <div
            class="result"
            v-for="hardScore in generationData.lessonplanHardScores"
            :key="hardScore.id"
          >
            <p class="result-description">{{`${hardScore.description}: `}}</p>
            <p class="result-value">{{hardScore.value}}</p>
          </div>
        </div>
        <div
          v-if="generationData && generationData.lessonplanSoftScores && generationData.lessonplanSoftScores.length"
        >
          <h4 class="subtitle">Unoptimal cases</h4>
          <div
            class="result"
            v-for="softScore in generationData.lessonplanSoftScores"
            :key="softScore.id"
          >
            <p class="result-description">{{`${softScore.description}: `}}</p>
            <p class="result-value">{{softScore.value}}</p>
          </div>
        </div>
      </div>
      <div class="btn-container">
        <v-btn
          dark
          color="#f5c21a"
          outlined
          class="btn btn-finish"
          @click="onSetupAgain"
        >Setup data again</v-btn>
        <v-btn
          dark
          color="#f5c21a"
          outlined
          class="btn btn-finish"
          @click="onGenerateClick"
        >Generate again</v-btn>
        <v-btn
          v-if="!hardScoresFailed"
          dark
          color="#f5c21a"
          class="btn btn-finish"
          :to="`/example-school/lessonplans`"
          target="_blank"
        >Check out lesson plans</v-btn>
      </div>
    </div>
  </div>
  <div v-else-if="generationError" class="container">
    <div>
      <div class="container-medium">
        <h3 class="title">Error occured during lesson plans generation</h3>
        <p
          class="description"
        >Something went wrong. You can try to change inserted data or try to generate lesson plans again.</p>
      </div>
      <div class="btn-container">
        <v-btn
          dark
          color="#f5c21a"
          outlined
          class="btn btn-finish"
          @click="onSetupAgain"
        >Setup data again</v-btn>
        <v-btn
          dark
          color="#f5c21a"
          outlined
          class="btn btn-finish"
          @click="onGenerateClick"
        >Generate again</v-btn>
      </div>
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
    ...mapState([
      'saveInProgress',
      'subjects',
      'generationData',
      'generationInProgress',
      'generationFinish',
      'generationError'
    ]),
    hardScoresFailed() {
      return (
        this.generationData &&
        this.generationData.lessonplanHardScores &&
        this.generationData.lessonplanHardScores.length &&
        this.generationData.lessonplanHardScores.some(score => score.value > 0)
      );
    },
    softScoresFailed() {
      return (
        this.generationData &&
        this.generationData.lessonplanSoftScores &&
        this.generationData.lessonplanSoftScores.length &&
        this.generationData.lessonplanSoftScores.some(score => score.value > 0)
      );
    }
  },
  data: () => ({
    generationProgressValue: 0,
    generationProgressValueInterval: 0
  }),
  watch: {
    generationProgressValue(val) {
      if (val >= 100) {
        clearInterval(this.generationProgressValueInterval);
      }
    }
  },
  methods: {
    ...mapActions([
      'generateLessonplans',
      'setGenerationResult',
      'getSubjects',
      'getWeekdays',
      'getLessons',
      'getClasses',
      'getTeachers',
      'getRooms',
      'getLessonplans'
    ]),
    onGenerateClick() {
      this.generationProgressValue = 0;
      this.generateLessonplans();

      clearInterval(this.generationProgressValueInterval);

      this.generationProgressValueInterval = setInterval(() => {
        this.generationProgressValue += 300 / 60; //Math.random() * (15 - 5) + 5;
      }, 3000);
    },
    onSetupAgain() {
      this.setGenerationResult({
        generationData: null,
        generationInProgress: false,
        generationFinish: false,
        generationError: false
      });
      this.getWeekdays();
      this.getLessons();
      this.getClasses();
      this.getSubjects();
      this.getTeachers();
      this.getRooms();
      this.getLessonplans();
      this.$router.push('/example-school/management/lessons');
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
.container-medium {
  margin: 25vh 0 0 0;
  width: 400px;
  text-align: center;
}
.max-width {
  width: 100%;
  display: flex;
  justify-content: center;
}
.title {
  margin: 0 0 20px 0;
  color: rgba(0, 0, 0, 0.87);
}
.subtitle {
  margin: 10px 0 20px 0;
  color: rgba(0, 0, 0, 0.87);
  width: 80%;
  text-align: center;
}
.description {
  margin: 0 0 25px 0;
  color: #6d6d6d;
}
.result {
  display: flex;
  /* margin: 0 0 5px 0; */
  color: #6d6d6d;
}
.result-description {
  width: 80%;
  text-align: left;
}
.result-value {
  width: 20%;
  padding: 0 12px;
  font-weight: bold;
}
.btn-container {
  width: 100%;
  text-align: center;
}
.btn-finish {
  margin: 20px 15px 20px 15px;
}
</style>