import Vue from 'vue'
import Vuex from 'vuex'
import MainApi from '@/api/MainApi'

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    error: null,
    classes: [],
    lessonplans: []
  },
  mutations: {
    SET_ERROR(state, error) {
      state.error = error
    },
    SET_CLASSES(state, classes) {
      state.classes = classes
    },
    SET_LESSONPLANS(state, lessonplans) {
      state.lessonplans = lessonplans
    },
  },
  actions: {
    async getClasses(context) {
      const { value, error } = await MainApi.getClasses()
      const { classes } = value

      if (error || !classes) {
        context.commit('SET_ERROR', error)
      } else {
        context.commit('SET_CLASSES', classes)
      }
    },
    async getLessonplans(context) {
      // TODO: ...
    }
  }
})
