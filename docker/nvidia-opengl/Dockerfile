# Based on the generic image
FROM codookie/xenial:cpp-tdd-env

MAINTAINER Andrei Gherghescu <gandrein@gmail.com>

LABEL Description="Ubuntu 16.04 Docker Container with development tools for CPP TDD with Nvidia & OpenGL support" Version="1.0"

# nvidia-docker hooks
LABEL com.nvidia.volumes.needed="nvidia_driver"
ENV PATH /usr/local/nvidia/bin:${PATH}
ENV LD_LIBRARY_PATH /usr/local/nvidia/lib:/usr/local/nvidia/lib64:${LD_LIBRARY_PATH}
