const getResponseValue = async (response) => {
    const contentType = response.headers.get("content-type");
    if (contentType && contentType.indexOf("application/json") !== -1) {
      return response.json()
    } else {
      return response.text()
    }
}

const fetchFromApi = async ({ path }) => {
    try {
        const response = await fetch(`http://localhost:8000/${path}`)

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
    })
}