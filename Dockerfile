FROM ubuntu:20.04
RUN apt update && apt install vim bazel
RUN git clone git@github.com:cjds/rpicar.git
WORKDIR /rpicar

