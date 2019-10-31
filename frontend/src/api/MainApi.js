const getResponseValue = async (response) => {
    const contentType = response.headers.get("content-type");
    if (contentType && contentType.indexOf("application/json") !== -1) {
        return response.json()
    } else {
        return response.text()
    }
}

const fetchFromApi = async ({ path, method = 'GET', body }) => {
    try {
        const headers = {
            method: method,
            headers: new Headers({ "Content-Type": "application/json" })
        };
        if (body) {
            headers.body = JSON.stringify(body)
        }
        const response = await fetch(`http://localhost:8000/${path}`, headers)

        if (!response.ok) {
            throw new Error(response.statusText)
        }

        const value = await getResponseValue(response)

        return {
            value: value,
            error: null
        }
    } catch (error) {
        console.log(err)

        return {
            value: null,
            error: error
        }
    }
}

export default {
    getClasses: async () => await fetchFromApi({
        path: 'lessonplans/classes'
    }),
    getLessonplans: async () => await fetchFromApi({
        path: 'lessonplans/lessonplans'
    })
}