# syntax=docker/dockerfile:1.0.0-experimental
FROM ubuntu:20.04 as base_stage
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install --yes curl gnupg2 git
RUN mkdir -p -m 0700 ~/.ssh && ssh-keyscan github.com >> ~/.ssh/known_hosts


FROM base_stage as git_stage
ARG GIT_CACHE_BREAK
RUN --mount=type=ssh git clone git@github.com:cjds/rpicar.git

FROM base_stage as dev_stage
COPY --from=git_stage /rpicar /rpicar
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install --yes curl gnupg2 git
RUN curl -s -N https://bazel.build/bazel-release.pub.gpg | apt-key add -
RUN curl -s -N https://raw.githubusercontent.com/git/git/master/contrib/completion/git-completion.bash -o ~/.git-completion.bash
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key|apt-key add -
RUN echo "deb [arch=amd64] https://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list
RUN apt update && DEBIAN_FRONTEND=noninteractive apt install --yes neovim bazel valgrind cppcheck wget clang-10 lldb-10 lld-10 libtinfo5 libgpiod-dev
RUN echo "source /rpicar/helpers.bash">> ~/.bashrc
RUN echo "source ~/.git-completion.bash">> ~/.bashrc

# Temp fix for this issue
# https://github.com/bazelbuild/bazel/issues/11554
RUN apt install -y python-is-python3
RUN curl -sL https://deb.nodesource.com/setup_14.x | bash -

RUN apt install -y nodejs
RUN npm install -g typescript
RUN npm install -g  parcel-bundler

WORKDIR /rpicar
