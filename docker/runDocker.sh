#!/bin/bash
SSH_PORT=22222 #you can connect via ssh onto this port
#note that the host directory path when using docker-toolbox has to start with "/c/Users/"
HOST_DIR=$PWD"/.." #path (Linux format!) to host directory to be shared with container
CONTAINER_DIR="/MyFS" #path (Linux format!) to the shared directory inside of the container
CONTAINER_NAME="bslab-container" #name of the launched docker container
IMAGE_NAME="iz-gitlab-01.hs-karlsruhe.de:4567/iwi-i/bslab" #name of the docker image to build and use
# RUN_COMMANDS="cp -r /MyFS/* ${CONTAINER_DIR}; cd ${CONTAINER_DIR}; ls obj; make"
RUN_COMMANDS="/usr/sbin/sshd; cd ${CONTAINER_DIR}; bash" #commands to run inside the container after starting the ssh daemon and before starting the interactive shell (bash)

echo "Building Docker Image '${IMAGE_NAME}':"
docker build -t "${IMAGE_NAME}" .
echo "
Running the Docker Container '${CONTAINER_NAME}' with Options:
Mounting ${HOST_DIR} to ${CONTAINER_DIR}
Run commands: ${RUN_COMMANDS}
SSH Daemon will be running and listening on Port ${SSH_PORT}.
User:     root
Password: root
"
docker run --privileged -it --rm -v "/${HOST_DIR}:/${CONTAINER_DIR}" --name "${CONTAINER_NAME}" -p "${SSH_PORT}":22 "${IMAGE_NAME}" bash -c "${RUN_COMMANDS}" #'bash' starts an interactive shell
