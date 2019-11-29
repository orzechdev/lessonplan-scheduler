<template>
  <div>
    <v-breadcrumbs :items="items" divider=">"></v-breadcrumbs>
    <v-list>
      <v-list-item
        v-for="classItem in classes"
        :key="classItem.name"
        :to="`/example-school/lessonplans/` + classItem.id"
      >{{ classItem.name }}</v-list-item>
      <v-list-item
        v-for="classItem in rooms"
        :key="classItem.name"
        :to="`/example-school/lessonplansRoom/` + classItem.id"
      >{{ classItem.name }}</v-list-item>
      <v-list-item
        v-for="classItem in teachers"
        :key="classItem.name"
        :to="`/example-school/lessonplansTeacher/` + classItem.id"
      >{{ classItem.name }}</v-list-item>
    </v-list>
  </div>
</template>

<script>
import { mapState } from 'vuex';

export default {
  name: 'lessonplans',
  computed: {
    ...mapState(['classes']),
    ...mapState(['teachers']),
    ...mapState(['rooms'])
  },
  data: () => ({
    items: [
      {
        text: 'Lessonplans'
      }
    ]
    // classes: [
    //   {
    //     id: "1",
    //     name: "1A"
    //   },
    //   {
    //     id: "2",
    //     name: "1B"
    //   }
    // ]
  })
};
</script>
