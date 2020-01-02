# Lesson plans scheduler

## Setup instruction

- Make sure you have Internet connection - docker needs to pull its images and package managers their dependencies. Also it is better to have more than few GB of memory available to run all services properly.
- Install [Docker with Docker Compose](https://docs.docker.com/get-docker/).
- From main project directory run `docker-compose up` - Docker will pull and build all images, than it should build algorithm and start backend after a while on http://0.0.0.0:8000/ as well as frontend on http://localhost:8080/ - make sure it is started before use.

## Usage

- 1st option - custom data - go to http://localhost:8080/#/example-school/management/lessons, insert some data, generate lesson plans and check them out on http://localhost:8080/#/example-school/lessonplans.
- 2nd option - predefined data - make requst to http://localhost:8000/lessonplans/saveData/?data-complexity=low, then go to go to http://localhost:8080/#/example-school/management/lessons, generate lesson plans and check them out on http://localhost:8080/#/example-school/lessonplans
