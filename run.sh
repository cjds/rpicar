#!/bin/bash
docker run -itd \
	-v ~/.ssh:/root/.ssh \
	-v ~/.vim:/root/.vim \
	-v ~/.git:/root/.git \
	--name rpicar --privileged --net=host rpicar:latest bash
