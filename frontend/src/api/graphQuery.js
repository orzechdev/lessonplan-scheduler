export const gql_query = {
  classes: `
    query {
      lessonplans_class {
        id
        name
      }
    }
  `,
  lessonplan_items: `
    query {
      lessonplans_lessonplanitem {
        id
        lessonplan_id
        class_model: lessonplans_class {
          name
          id
        }
        lesson: lessonplans_lesson {
          end_time
          id
          name
          start_time
        }
        room: lessonplans_room {
          id
          name
        }
        teacher: lessonplans_teacher {
          id
          name
        }
        subject: lessonplans_subject {
          id
          name
        }
        weekday: lessonplans_weekday {
          id
          name
        }
      }
    }
  `
};
