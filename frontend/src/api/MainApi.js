import gqlQuery from './graphQuery';

const getResponseValue = async response => {
  const contentType = response.headers.get('content-type');
  if (contentType && contentType.indexOf('application/json') !== -1) {
    return response.json();
  }
  return response.text();
};

const fetchFromApi = async ({ path, method = 'GET', body }) => {
  try {
    const headers = {
      method,
      headers: { 'Content-Type': 'application/json' }
    };
    if (body) {
      headers.body = JSON.stringify(body);
    }
    // eslint-disable-next-line no-undef
    const response = await fetch(path, headers);

    if (!response.ok) {
      throw new Error(response.statusText);
    }

    const value = await getResponseValue(response);

    return {
      value,
      error: null
    };
  } catch (error) {
    // eslint-disable-next-line no-console
    console.log(error);

    return {
      value: null,
      error
    };
  }
};

const fetchFromRestApi = async ({ path, method = 'GET', body }) => {
  const response = await fetchFromApi({
    path: `http://localhost:8000/${path}`,
    method,
    body
  });
  return response;
};

const fetchFromGraphApi = async ({ method = 'POST', body }) => {
  const response = await fetchFromApi({
    path: `http://localhost:8000/graphql`,
    method,
    body
  });
  return response;
};

export default {
  saveWeekDays: async () => {
    const response = await fetchFromRestApi({
      path: `lessonplans/saveWeekDays`
    });
    return response;
  },
  getLessonplans: async () => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.lessonplansItems
      }
    });
    return response;
  },
  getClasses: async () => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.classes
      }
    });
    return response;
  },
  getTeachers: async () => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.teachers
      }
    });
    return response;
  },
  getRooms: async () => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.rooms
      }
    });
    return response;
  },
  getWeekdays: async () => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.weekdays
      }
    });
    return response;
  },
  getLessons: async () => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.lessons
      }
    });
    return response;
  },
  getSubjects: async () => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.subjects
      }
    });
    return response;
  },
  getWeekday: async id => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.weekday,
        variables: { id }
      }
    });
    return response;
  },
  getLesson: async id => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.lesson,
        variables: { id }
      }
    });
    return response;
  },
  getClass: async id => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.class,
        variables: { id }
      }
    });
    return response;
  },
  createLesson: async (lessonNumber, startTime, endTime) => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.createLesson,
        variables: { name: lessonNumber, startTime, endTime }
      }
    });
    return response;
  },
  createRoom: async roomName => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.createRoom,
        variables: { name: roomName }
      }
    });
    return response;
  },
  createSubject: async subjectName => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.createSubject,
        variables: { name: subjectName }
      }
    });
    return response;
  },
  createTeacher: async (fullName, subjectsIds) => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.createTeacher,
        variables: { name: fullName, subjectsIds }
      }
    });
    return response;
  },
  createClass: async (name, subjectsData) => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.createClass,
        variables: { name, classSubjects: subjectsData }
      }
    });
    return response;
  },
  updateLesson: async (id, lessonNumber, startTime, endTime) => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.updateLesson,
        variables: { id, name: lessonNumber, startTime, endTime }
      }
    });
    return response;
  },
  updateRoom: async (id, roomName) => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.updateRoom,
        variables: { id, name: roomName }
      }
    });
    return response;
  },
  updateSubject: async (id, subjectName) => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.updateSubject,
        variables: { id, name: subjectName }
      }
    });
    return response;
  },
  updateTeacher: async (id, fullName, subjectsIds) => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.updateTeacher,
        variables: { id, name: fullName, subjectsIds }
      }
    });
    return response;
  },
  updateClass: async (id, name, subjectsData) => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.updateClass,
        variables: { id, name, classSubjects: subjectsData }
      }
    });
    return response;
  },
  deleteLesson: async id => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.deleteLesson,
        variables: { id }
      }
    });
    return response;
  },
  deleteRoom: async id => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.deleteRoom,
        variables: { id }
      }
    });
    return response;
  },
  deleteSubject: async id => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.deleteSubject,
        variables: { id }
      }
    });
    return response;
  },
  deleteTeacher: async id => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.deleteTeacher,
        variables: { id }
      }
    });
    return response;
  },
  deleteClass: async id => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.deleteClass,
        variables: { id }
      }
    });
    return response;
  },
  generateLessonplans: async () => {
    const response = await fetchFromRestApi({
      path: `lessonplans/generate/?algorithm-type=genetic`
    });
    return response;
  }
};
