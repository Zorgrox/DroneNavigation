#!/bin/bash

ROOTDIR=`git rev-parse --show-toplevel`
source ${ROOTDIR}/config/settings

docker pull ${DOCKER_IMAGE_PREFIX}/base

docker build $1 \
	--target env \
	--build-arg USER_ID=$(id -u) \
	--build-arg GROUP_ID=$(id -g) \
	-t ${DOCKER_IMAGE_PREFIX}/env "$ROOTDIR"
