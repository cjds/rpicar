# syntax=docker/dockerfile:1.0.0-experimental
FROM ubuntu:20.04 as base_stage
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install --yes curl gnupg2 git
RUN mkdir -p -m 0700 ~/.ssh && ssh-keyscan github.com >> ~/.ssh/known_hosts


FROM base_stage as git_stage
RUN --mount=type=ssh git clone git@github.com:cjds/rpicar.git

FROM base_stage as dev_stage
COPY --from=git_stage /rpicar /rpicar
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install --yes curl gnupg2 git
RUN bash -c "curl -s -N https://bazel.build/bazel-release.pub.gpg | apt-key add -"
RUN echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install --yes vim bazel clang valgrind cppcheck
RUN echo "source /rpicar/helpers.bash">> ~/.bashrc

WORKDIR /rpicar
