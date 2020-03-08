#!/bin/bash
docker run -itd -v ~/.ssh:/root/.ssh --name rpicar --privileged --net=host rpicar:latest bash
