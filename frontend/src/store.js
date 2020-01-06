/* eslint-disable no-param-reassign */
import Vue from 'vue';
import Vuex from 'vuex';
// eslint-disable-next-line import/no-unresolved
import MainApi from '@/api/MainApi';

Vue.use(Vuex);

export default new Vuex.Store({
  state: {
    error: null,
    saveInProgress: false,
    weekdays: [],
    lessons: [],
    classes: [],
    subjects: [],
    teachers: [],
    rooms: [],
    lessonplans: [],
    generationData: null,
    generationInProgress: false,
    generationFinish: false,
    generationError: false
  },
  mutations: {
    SET_ERROR(state, error) {
      state.error = error;
    },
    SET_SAVE_IN_PROGRESS(state, saveInProgress) {
      state.saveInProgress = saveInProgress;
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
    SET_WEEKDAYS(state, weekdays) {
      state.weekdays = weekdays;
    },
    SET_LESSONS(state, lessons) {
      state.lessons = lessons;
    },
    SET_SUBJECTS(state, subjects) {
      state.subjects = subjects;
    },
    SET_LESSONPLANS(state, lessonplans) {
      state.lessonplans = lessonplans;
    },
    SET_GENERATION_RESULT(state, generationResult) {
      state.generationData = generationResult.generationData;
      state.generationInProgress = generationResult.generationInProgress;
      state.generationFinish = generationResult.generationFinish;
      state.generationError = generationResult.generationError;
    }
  },
  actions: {
    async saveWeekDays(context) {
      const { value, error } = await MainApi.saveWeekDays();

      if (error || !value) {
        context.commit('SET_ERROR', error);
      }
    },
    async getWeekdays(context) {
      const { value, error } = await MainApi.getWeekdays();

      if (error || !value || !value.data || !value.data.allWeekdays) {
        context.commit('SET_ERROR', error);
      } else {
        context.commit('SET_WEEKDAYS', value.data.allWeekdays);
      }
    },
    async getLessons(context) {
      const { value, error } = await MainApi.getLessons();

      if (error || !value || !value.data || !value.data.allLessons) {
        context.commit('SET_ERROR', error);
      } else {
        context.commit('SET_LESSONS', value.data.allLessons);
      }
    },
    async getSubjects(context) {
      const { value, error } = await MainApi.getSubjects();

      if (error || !value || !value.data || !value.data.allSubjects) {
        context.commit('SET_ERROR', error);
      } else {
        context.commit('SET_SUBJECTS', value.data.allSubjects);
      }
    },
    async getClasses(context) {
      const { value, error } = await MainApi.getClasses();

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
    },
    async createLesson(context, payload) {
      const { lessonNumber, startTime, endTime } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.createLesson(lessonNumber, startTime, endTime);

      if (error || !value || !value.data || !value.data.createLesson) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getLessons');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async createRoom(context, payload) {
      const { roomName } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.createRoom(roomName);

      if (error || !value || !value.data || !value.data.createRoom) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getRooms');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async createSubject(context, payload) {
      const { subjectName } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.createSubject(subjectName);

      if (error || !value || !value.data || !value.data.createSubject) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getSubjects');
        context.dispatch('getTeachers');
        context.dispatch('getClasses');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async createTeacher(context, payload) {
      const { fullName, subjectsIds } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.createTeacher(fullName, subjectsIds);

      if (error || !value || !value.data || !value.data.createTeacher) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getTeachers');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async createClass(context, payload) {
      const { className, subjectsData } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.createClass(className, subjectsData);

      if (error || !value || !value.data || !value.data.createClass) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getClasses');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async updateLesson(context, payload) {
      const { id, lessonNumber, startTime, endTime } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.updateLesson(id, lessonNumber, startTime, endTime);

      if (error || !value || !value.data || !value.data.updateLesson) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getLessons');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async updateRoom(context, payload) {
      const { id, roomName } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.updateRoom(id, roomName);

      if (error || !value || !value.data || !value.data.updateRoom) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getRooms');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async updateSubject(context, payload) {
      const { id, subjectName } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.updateSubject(id, subjectName);

      if (error || !value || !value.data || !value.data.updateSubject) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getSubjects');
        context.dispatch('getTeachers');
        context.dispatch('getClasses');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async updateTeacher(context, payload) {
      const { id, fullName, subjectsIds } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.updateTeacher(id, fullName, subjectsIds);

      if (error || !value || !value.data || !value.data.updateTeacher) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getTeachers');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async updateClass(context, payload) {
      const { id, className, subjectsData } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.updateClass(id, className, subjectsData);

      if (error || !value || !value.data || !value.data.updateClass) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getClasses');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async deleteLesson(context, payload) {
      const { id } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.deleteLesson(id);

      if (error || !value || !value.data || !value.data.deleteLesson) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getLessons');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async deleteRoom(context, payload) {
      const { id } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.deleteRoom(id);

      if (error || !value || !value.data || !value.data.deleteRoom) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getRooms');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async deleteSubject(context, payload) {
      const { id } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.deleteSubject(id);

      if (error || !value || !value.data || !value.data.deleteSubject) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getSubjects');
        context.dispatch('getTeachers');
        context.dispatch('getClasses');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async deleteTeacher(context, payload) {
      const { id } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.deleteTeacher(id);

      if (error || !value || !value.data || !value.data.deleteTeacher) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getTeachers');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async deleteClass(context, payload) {
      const { id } = payload;
      context.commit('SET_SAVE_IN_PROGRESS', true);
      const { value, error } = await MainApi.deleteClass(id);

      if (error || !value || !value.data || !value.data.deleteClass) {
        context.commit('SET_ERROR', error);
      } else {
        context.dispatch('getClasses');
      }
      context.commit('SET_SAVE_IN_PROGRESS', false);
    },
    async setGenerationResult(context, payload) {
      context.commit('SET_GENERATION_RESULT', payload);
    },
    async generateLessonplans(context) {
      context.dispatch('setGenerationResult', {
        generationData: null,
        generationInProgress: true,
        generationFinish: false,
        generationError: false
      });
      const { value, error } = await MainApi.generateLessonplans();

      if (error || !value || !value.result || value.result !== 'ok') {
        context.dispatch('setGenerationResult', {
          generationData: null,
          generationInProgress: false,
          generationFinish: false,
          generationError: true
        });
      } else {
        context.dispatch('setGenerationResult', {
          generationData: value,
          generationInProgress: false,
          generationFinish: true,
          generationError: false
        });
      }
    }
  }
});
