#!/bin/bash

ROOTDIR=`git rev-parse --show-toplevel`
source ${ROOTDIR}/config/settings

docker tag ${DOCKER_IMAGE_PREFIX}/base csci3081base

docker build $1 \
	--target sim \
	--build-arg DEP_DIR=${DEP_DIR} \
	-t ${DOCKER_IMAGE_PREFIX}/sim "$ROOTDIR/project"
	