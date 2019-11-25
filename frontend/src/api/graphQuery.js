const gqlQuery = {
  classes: `
    query {
      allClasses {
        id
        name
      }
    }
  `,
  class: `
    query Class($id: Int) {
      classModel(id: $id) {
        name
        id
      }
    }
  `,
  lessonplansItems: `
    query {
      allLessonplansItems {
        id
        weekday {
          id
          name
        }
        lesson {
          id
          name
          startTime
          endTime
        }
        classModel {
          id
          name
        }
        subject {
          id
          name
        }
        teacher {
          id
          name
        }
        room {
          id
          name
        }
      }
    }
  `
};

export default gqlQuery;
