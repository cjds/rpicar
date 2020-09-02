#!/bin/bash
docker run -itd \
	-v ~/.ssh:/root/.ssh \
	-v ~/.vim:/root/.vim \
	-v ~/.vimrc:/root/.vimrc \
	-v ~/.git:/root/.git \
	-v ~/.gitconfig:/root/.gitconfig \
	-v $PWD:/rpicar \
	--name rpicar --privileged --net=host rpicar:latest bash
