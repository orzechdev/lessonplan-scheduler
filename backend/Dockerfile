FROM python:3
ENV PYTHONUNBUFFERED 1
COPY wait-for-it.sh /wait-for-it.sh
RUN chmod +x /wait-for-it.sh
RUN mkdir /backend
WORKDIR /backend
COPY requirements.txt /backend/
RUN pip install -r requirements.txt
COPY . /backend/
