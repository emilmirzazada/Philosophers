FROM ubuntu:16.04

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install g++ valgrind -y
RUN apt-get update && apt-get install make
RUN apt-get update && apt-get install -y \
    build-essential \
    libpthread-stubs0-dev
ENV NUM_THREADS=4
