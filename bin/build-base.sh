#!/bin/bash

ROOTDIR=`git rev-parse --show-toplevel`
source ${ROOTDIR}/config/settings

docker build --target base --build-arg DEP_DIR=${DEP_DIR} -t ${DOCKER_IMAGE_PREFIX}/base ${ROOTDIR}/env

docker push ${DOCKER_IMAGE_PREFIX}/base
