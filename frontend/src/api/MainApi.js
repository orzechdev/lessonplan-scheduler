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
      method: method,
      headers: { 'Content-Type': 'application/json' }
    };
    if (body) {
      headers.body = JSON.stringify(body);
    }
    const response = await fetch(path, headers);

    if (!response.ok) {
      throw new Error(response.statusText);
    }

    const value = await getResponseValue(response);

    return {
      value: value,
      error: null
    };
  } catch (error) {
    console.log(error);

    return {
      value: null,
      error: error
    };
  }
};

const fetchFromRestApi = async ({ path, method = 'GET', body }) => {
  return await fetchFromApi({
    path: `http://localhost:8000/${path}`,
    method,
    body
  });
};

const fetchFromGraphApi = async ({ method = 'POST', body }) => {
  return await fetchFromApi({
    path: `http://localhost:8000/graphql`,
    method,
    body
  });
};

export default {
  getLessonplans: async () => {
    const response = fetchFromGraphApi({
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
  getClass: async () => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.class,
        variables: { id: 141 }
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
  createTeacher: async fullName => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.createRoom,
        variables: { name: fullName }
      }
    });
    return response;
  },
  createClass: async name => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.createClass,
        variables: { name }
      }
    });
    return response;
  }
};
