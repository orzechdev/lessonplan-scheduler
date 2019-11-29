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
  getLessonplans: async () =>
    await fetchFromGraphApi({
      body: {
        query: gqlQuery.lessonplansItems
      }
    }),
  getClasses: async () =>
    await fetchFromGraphApi({
      body: {
        query: gqlQuery.classes
      }
    }),
  getTeachers: async () =>
    await fetchFromGraphApi({
      body: {
        query: gqlQuery.teachers
      }
    }),
  getRooms: async () =>
    await fetchFromGraphApi({
      body: {
        query: gqlQuery.rooms
      }
    }),
  getClass: async () => {
    const response = await fetchFromGraphApi({
      body: {
        query: gqlQuery.class,
        variables: { id: 141 }
      }
    });
    return response;
  }
};
