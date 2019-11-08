FROM node:12.8.0-alpine
RUN apk add --no-cache bash
RUN yarn global add @vue/cli @vue/cli-service
RUN mkdir /frontend
WORKDIR /frontend
COPY package.json yarn.lock ./frontend/
RUN cd ./frontend && yarn install
COPY . ./frontend/
