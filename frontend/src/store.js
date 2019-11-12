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

      if (error || !value || !value.data || !value.data.lessonplans_class) {
        context.commit('SET_ERROR', error)
      } else {
        context.commit('SET_CLASSES', value.data.lessonplans_class)
      }
    },
    async getLessonplans(context) {
      const { value, error } = await MainApi.getLessonplans()
      
      if (error || !value || !value.data || !value.data.lessonplans_lessonplanitem) {
        context.commit('SET_ERROR', error)
      } else {
        context.commit('SET_LESSONPLANS', value.data.lessonplans_lessonplanitem)
      }
    }
  }
})
