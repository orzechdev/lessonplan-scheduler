# Lesson plans scheduler

## Setup instruction

- Install [Docker with Docker Compose](https://docs.docker.com/get-docker/)
- From main project directory run `docker-compose up`

## Usage

- 1st option - custom data - go to http://localhost:8080/#/example-school/management/lessons, insert some data, generate lesson plans and check them out on http://localhost:8080/#/example-school/lessonplans.
- 2nd option - predefined data - make requst to http://localhost:8000/lessonplans/saveData/?data-complexity=low, then go to go to http://localhost:8080/#/example-school/management/lessons, generate lesson plans and check them out on http://localhost:8080/#/example-school/lessonplans
