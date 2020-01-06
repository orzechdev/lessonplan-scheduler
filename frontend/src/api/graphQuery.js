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
        classsubjectSet {
          countInWeek
          subject {
            id
            name
          }
        }
      }
    }
  `,
  teachers: `
    query {
      allTeachers {
        id
        name
        teachersubjectSet {
          subject {
            id
            name
          }
        }
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
  lesson: `
    query Lesson($id: Int) {
      lesson(id: $id) {
        id
        name
        startTime
        endTime
      }
    }
  `,
  weekday: `
    query Weekday ($id: Int) {
      weekday(id: $id) {
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
  `,
  updateLesson: `
    mutation UpdateLesson($id: Int!, $name: Int!, $startTime: Time!, $endTime: Time!) {
      updateLesson(id: $id, name: $name, startTime: $startTime, endTime: $endTime) {
        lesson {
          id
          name
          startTime
          endTime
        }
      }
    }
  `,
  updateRoom: `
    mutation UpdateRoom($id: Int!, $name: String!) {
      updateRoom(id: $id, name: $name) {
        room {
          id
          name
        }
      }
    }
  `,
  updateSubject: `
    mutation UpdateSubject($id: Int!, $name: String!) {
      updateSubject(id: $id, name: $name) {
        subject {
          id
          name
        }
      }
    }
  `,
  updateTeacher: `
    mutation UpdateTeacher($id: Int!, $name: String!, $subjectsIds: [Int]!) {
      updateTeacher(id: $id, name: $name, subjectsIds: $subjectsIds) {
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
  updateClass: `
    mutation UpdateClass($id: Int!, $name: String!, $classSubjects: [ClassSubjectInput]!) {
      updateClass(id: $id, name: $name, subjects: $classSubjects) {
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
  `,
  deleteLesson: `
    mutation DeleteLesson($id: Int!) {
      deleteLesson(id: $id) {
        ok
      }
    }
  `,
  deleteRoom: `
    mutation DeleteRoom($id: Int!) {
      deleteRoom(id: $id) {
        ok
      }
    }
  `,
  deleteSubject: `
    mutation DeleteSubject($id: Int!) {
      deleteSubject(id: $id) {
        ok
      }
    }
  `,
  deleteTeacher: `
    mutation DeleteTeacher($id: Int!) {
      deleteTeacher(id: $id) {
        ok
      }
    }
  `,
  deleteClass: `
    mutation DeleteClass($id: Int!) {
      deleteClass(id: $id) {
        ok
      }
    }
  `
};

export default gqlQuery;
