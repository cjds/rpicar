#!/bin/bash
eval $(ssh-agent)
ssh-add ~/.ssh/id_rsa
DOCKER_BUILDKIT=1 docker build --build-arg GIT_CACHE_BREAK="$(date)" --ssh default . -t rpicar:latest
