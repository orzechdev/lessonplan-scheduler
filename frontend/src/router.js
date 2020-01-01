import Vue from 'vue';
import Router from 'vue-router';
import MainWrapper from './MainWrapper.vue';
import ManagementWrapper from './ManagementWrapper.vue';
import Lessonplans from './views/Lessonplans.vue';
import Timetable from './views/Timetable.vue';
import TimetableRoom from './views/TimetableRoom.vue';
import TimetableTeacher from './views/TimetableTeacher.vue';
import AddLessonList from './views/AddLessonList.vue';
import AddLesson from './views/AddLesson.vue';
import AddRoomList from './views/AddRoomList.vue';
import AddRoom from './views/AddRoom.vue';
import AddSubjectList from './views/AddSubjectList.vue';
import AddSubject from './views/AddSubject.vue';
import AddTeacherList from './views/AddTeacherList.vue';
import AddTeacher from './views/AddTeacher.vue';
import AddClassList from './views/AddClassList.vue';
import AddClass from './views/AddClass.vue';
import Generate from './views/Generate.vue';

Vue.use(Router);

const router = new Router({
  routes: [
    {
      path: '/example-school',
      component: MainWrapper,
      children: [
        {
          path: 'lessonplans',
          name: 'Example School',
          component: Lessonplans
        },
        {
          path: 'lessonplans/:classId',
          name: 'about',
          component: Timetable,
          props: true
        },
        {
          path: 'lessonplansRoom/:classId',
          name: 'about',
          component: TimetableRoom,
          props: true
        },
        {
          path: 'lessonplansTeacher/:classId',
          name: 'about',
          component: TimetableTeacher,
          props: true
        }
      ]
    },
    {
      path: '/example-school/management',
      component: ManagementWrapper,
      props: {
        whiteBackground: true
      },
      children: [
        {
          path: 'lessons',
          name: 'lessons',
          component: AddLessonList
        },
        {
          path: 'lessons/add',
          name: 'add lesson',
          component: AddLesson,
          props: { customAppBar: true }
        },
        {
          path: 'rooms',
          name: 'rooms',
          component: AddRoomList
        },
        {
          path: 'rooms/add',
          name: 'add room',
          component: AddRoom,
          props: { customAppBar: true }
        },
        {
          path: 'subjects',
          name: 'subjects',
          component: AddSubjectList
        },
        {
          path: 'subjects/add',
          name: 'add subject',
          component: AddSubject,
          props: { customAppBar: true }
        },
        {
          path: 'teachers',
          name: 'teachers',
          component: AddTeacherList
        },
        {
          path: 'teachers/add',
          name: 'add teacher',
          component: AddTeacher,
          props: { customAppBar: true }
        },
        {
          path: 'classes',
          name: 'classes',
          component: AddClassList
        },
        {
          path: 'classes/add',
          name: 'add class',
          component: AddClass,
          props: { customAppBar: true }
        },
        {
          path: 'generate',
          name: 'generate',
          component: Generate,
          props: { customAppBar: true }
        }
      ]
    }
  ]
});
// router.replace({ path: '/example-school/lessonplans', redirect: '/' }).catch(() => {});
// router.replace({ path: '/example-school/lessonplans', redirect: '/#' }).catch(() => {});
// router.replace({ path: '/example-school/lessonplans', redirect: '/#/' }).catch(() => {});

export default router;
