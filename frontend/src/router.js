import Vue from 'vue'
import Router from 'vue-router'
import Lessonplans from './views/Lessonplans.vue'
import Timetable from './views/Timetable.vue'

Vue.use(Router)

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
    }
  ]
})
router.replace({ path: '/example-school/lessonplans', redirect: '/' })
router.replace({ path: '/example-school/lessonplans', redirect: '/#' })
router.replace({ path: '/example-school/lessonplans', redirect: '/#/' })

export default router