#!/bin/bash

###
#
# This file is based on work by Henning Häcker
# https://github.com/hacker-h/bsuebung-docker
#
###

### begin of configuration ###

# you can connect via ssh onto this port
SSH_PORT=22222 

# path (Windows format!) to host directory to be shared with container
HOST_DIR="$(echo $PWD | sed -e 's/^\///' -e 's/\//\\/g' -e 's/^./\0:/')\.." 

# path (Linux format!) to the shared directory inside of the container
CONTAINER_DIR="/MyFS" 

# name of the launched docker container
CONTAINER_NAME="bslab-container" 

# name of the docker image to build and use
IMAGE_NAME="iz-gitlab-01.hs-karlsruhe.de:4567/iwi-i/bslab" 

# commands to run inside the container 
RUN_COMMANDS="/usr/sbin/sshd; cd ${CONTAINER_DIR}; bash" 

#
CONTAINER_REGISTRY="iz-gitlab-01.hs-karlsruhe.de:4567"
DT_USEER="gitlab+deploy-token-1"
DT_PASSWD="vPMZ1WAoG1NjXGZP5xrb"

### End of configuration ###

# login to container registry
echo "Login into container registry '${CONTAINER_REGISTRY}':"
docker login -u ${DT_USEER} -p ${DT_PASSWD} ${CONTAINER_REGISTRY}

# build docker imgage
echo "Building Docker Image '${IMAGE_NAME}':"
docker build -t "${IMAGE_NAME}" .

# run container
echo "
Running the Docker Container '${CONTAINER_NAME}' with Options:
Mounting ${HOST_DIR} to ${CONTAINER_DIR}
Run commands: ${RUN_COMMANDS}
SSH Daemon will be running and listening on Port ${SSH_PORT}.
User:     root
Password: root
"
winpty docker run --tty --privileged -it --rm -v "/${HOST_DIR}:/${CONTAINER_DIR}" --name "${CONTAINER_NAME}" -p "${SSH_PORT}":22 "${IMAGE_NAME}" bash -c "${RUN_COMMANDS}" #'bash' starts an interactive shell
