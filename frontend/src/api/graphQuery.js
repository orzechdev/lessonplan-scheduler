const gqlQuery = {
  lessons: `
    query {
      allLessons {
        id
        name
        startTime
        endTime
      }
    }
  `,
  weekdays: `
    query {
      allWeekdays {
        id
        name
      }
    }
  `,
  subjects: `
    query {
      allSubjects {
        id
        name
      }
    }
  `,
  classes: `
    query {
      allClasses {
        id
        name
      }
    }
  `,
  teachers: `
    query {
      allTeachers {
        id
        name
      }
    }
  `,
  rooms: `
    query {
      allRooms {
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
  `,
  createLesson: `
    mutation CreateLesson($name: String!, $startTime: Time!, $endTime: Time!) {
      createLesson(name: $name, startTime: $startTime, endTime: $endTime) {
        lesson {
          id
          name
          startTime
          endTime
        }
      }
    }
  `,
  createRoom: `
    mutation CreateRoom($name: String!) {
      createRoom(name: $name) {
        room {
          id
          name
        }
      }
    }
  `,
  createSubject: `
    mutation CreateSubject($name: String!) {
      createSubject(name: $name) {
        subject {
          id
          name
        }
      }
    }
  `,
  createTeacher: `
    mutation CreateTeacher($name: String!, $subjectsIds: [Int]!) {
      createTeacher(name: $name, subjectsIds: $subjectsIds) {
        teacher {
          id
          name
        }
        teacherSubjects {
          id
          name
        }
      }
    }
  `,
  createClass: `
    mutation CreateClass($name: String!, $classSubjects: [ClassSubjectInput]!) {
      createClass(name: $name, subjects: $classSubjects) {
        classModel {
          id
          name
        }
        classSubjects {
          subject {
            id
            name
          }
          countInWeek
        }
      }
    }
  `
};

export default gqlQuery;
