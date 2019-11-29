import Vue from 'vue';
import Router from 'vue-router';
import Lessonplans from './views/Lessonplans.vue';
import Timetable from './views/Timetable.vue';
import TimetableRoom from './views/TimetableRoom.vue';
import TimetableTeacher from './views/TimetableTeacher.vue';

Vue.use(Router);

const router = new Router({
  routes: [
    {
      path: '/example-school/lessonplans',
      name: 'Example School',
      component: Lessonplans
    },
    {
      path: '/example-school/lessonplans/:classId',
      name: 'about',
      component: Timetable,
      props: true
    },
    {
      path: '/example-school/lessonplansRoom/:classId',
      name: 'about',
      component: TimetableRoom,
      props: true
    },
    {
      path: '/example-school/lessonplansTeacher/:classId',
      name: 'about',
      component: TimetableTeacher,
      props: true
    }
  ]
});
router.replace({ path: '/example-school/lessonplans', redirect: '/' }).catch(() => {});
router.replace({ path: '/example-school/lessonplans', redirect: '/#' }).catch(() => {});
router.replace({ path: '/example-school/lessonplans', redirect: '/#/' }).catch(() => {});

export default router;
