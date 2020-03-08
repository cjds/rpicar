#!/bin/bash
eval $(ssh-agent)
ssh-add ~/.ssh/id_rsa
DOCKER_BUILDKIT=1 docker build --ssh default . -t rpicar:latest
