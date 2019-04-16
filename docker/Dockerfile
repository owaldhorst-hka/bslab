###
#
# This file is based on work by Henning Häcker
# https://github.com/hacker-h/bsuebung-docker
#
###

From rastasheep/ubuntu-sshd:18.04

RUN apt-get clean && \
    apt-get update &&\
    apt-get install -y \ 
# Install development environment
        build-essential \
        cmake \
        fuse \
        libfuse-dev \
        pkg-config \
        gdb \
        valgrind \
        rsync \
        less \
        vim \
        nano \                 
# Configure Locale
        locales && \
    sed --in-place '/en_US.UTF-8/s/^#//' /etc/locale.gen && \
    locale-gen en_US.UTF-8 && \
# Clean up
    rm -rf /var/lib/apt/lists/* /usr/src/*

# Set environment variables    
ENV LANG en_US.UTF-8
ENV LANGUAGE en_US.UTF-8
ENV LC_ALL en_US.UTF-8

# Configure volumes
VOLUME /MyFS
VOLUME /tmp
VOLUME /root