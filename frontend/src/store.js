import Vue from 'vue';
import Vuex from 'vuex';
import MainApi from '@/api/MainApi';

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    error: null,
    classes: [],
    teachers: [],
    rooms: [],
    lessonplans: []
  },
  mutations: {
    SET_ERROR(state, error) {
      state.error = error;
    },
    SET_CLASSES(state, classes) {
      state.classes = classes;
    },
    SET_TEACHERS(state, teachers) {
      state.teachers = teachers;
    },
    SET_ROOMS(state, rooms) {
      state.rooms = rooms;
    },
    SET_LESSONPLANS(state, lessonplans) {
      state.lessonplans = lessonplans;
    }
  },
  actions: {
    async getClasses(context) {
      const { value, error } = await MainApi.getClasses();
      const { value2, error2 } = await MainApi.getClass();

      if (error || !value || !value.data || !value.data.allClasses) {
        context.commit('SET_ERROR', error);
      } else {
        context.commit('SET_CLASSES', value.data.allClasses);
      }
    },
    async getTeachers(context) {
      const { value, error } = await MainApi.getTeachers();

      if (error || !value || !value.data || !value.data.allTeachers) {
        context.commit('SET_ERROR', error);
      } else {
        context.commit('SET_TEACHERS', value.data.allTeachers);
      }
    },
    async getRooms(context) {
      const { value, error } = await MainApi.getRooms();

      if (error || !value || !value.data || !value.data.allRooms) {
        context.commit('SET_ERROR', error);
      } else {
        context.commit('SET_ROOMS', value.data.allRooms);
      }
    },
    async getLessonplans(context) {
      const { value, error } = await MainApi.getLessonplans();

      if (error || !value || !value.data || !value.data.allLessonplansItems) {
        context.commit('SET_ERROR', error);
      } else {
        context.commit('SET_LESSONPLANS', value.data.allLessonplansItems);
      }
    }
  }
});
