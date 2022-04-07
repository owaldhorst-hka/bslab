ARG VARIANT=debian-11
FROM mcr.microsoft.com/vscode/devcontainers/cpp:0-${VARIANT}

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get clean && \
    apt-get update &&\
    apt-get install -y \ 
        build-essential \
        cmake \
        fuse \
        libfuse-dev \
        pkg-config \
        gdb \
        valgrind \
        doxygen
