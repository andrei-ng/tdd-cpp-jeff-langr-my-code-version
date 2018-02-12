FROM ubuntu:xenial

MAINTAINER Andrei Gherghescu <gandrein@gmail.com>

LABEL Description="Ubuntu 16.04 Docker Container with development tools for CPP TDD" Version="1.0"

# Arguments
ARG user=docker
ARG uid=1000
ARG shell=/bin/bash

# ------------------------------------------ Install required (&useful) packages --------------------------------------
RUN apt-get update && apt-get install -y \
 software-properties-common \
 lsb-release mesa-utils \
 x11-apps locales\
 gdb valgrind \
 build-essential cmake \
 git subversion \
 nano vim \
 gnome-terminal terminator \
 wget curl unzip \
 sudo htop ssh zsh screen tree \
 astyle clang-format \
 libjsoncpp1 libjsoncpp-dev \
 libcanberra-gtk* \
 && add-apt-repository ppa:nholthaus/gtest-runner -y \
 && apt-get update && apt-get install gtest-runner libqt5opengl5 libqt5xml5 -y \
 && sudo locale-gen en_US.UTF-8 \
 && rm -rf /var/lib/apt/lists/* \
 && apt-get clean

# Configure timezone and locale 
ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8

# ---------------------------------- User enviroment config  -----------------------------
# Crete and add user
RUN useradd -ms ${shell} ${user}
ENV USER=${user}

RUN export uid=${uid} gid=${uid}

RUN \
  mkdir -p /etc/sudoers.d && \
  echo "${user}:x:${uid}:${uid}:${user},,,:$HOME:${shell}" >> /etc/passwd && \
  echo "${user}:x:${uid}:" >> /etc/group && \
  echo "${user} ALL=(ALL) NOPASSWD: ALL" > "/etc/sudoers.d/${user}" && \
  chmod 0440 "/etc/sudoers.d/${user}"

# Switch to user
USER ${user}

# Install and configure OhMyZSH
RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh || true \
 && git clone https://github.com/sindresorhus/pure $HOME/.oh-my-zsh/custom/pure \
 && ln -s $HOME/.oh-my-zsh/custom/pure/pure.zsh-theme $HOME/.oh-my-zsh/custom/ \
 && ln -s $HOME/.oh-my-zsh/custom/pure/async.zsh $HOME/.oh-my-zsh/custom/ \
 && sed -i -e 's/robbyrussell/refined/g' $HOME/.zshrc

# Copy Terminator Configuration file
# '$HOME' does not seem to work with the COPY directive
RUN mkdir -p $HOME/.config/terminator/
COPY configs/terminator_config /home/${user}/.config/terminator/config
COPY configs/bash_aliases /home/${user}/.bash_aliases
COPY entrypoint.sh /home/${user}/entrypoint.sh
RUN sudo chmod +x /home/${user}/entrypoint.sh \
 && sudo chown ${user}:${user} /home/${user}/entrypoint.sh \
  	/home/${user}/.config/terminator/config \
  	/home/${user}/.bash_aliases

# Create a mount point to bind host data to
VOLUME /extern

# Make SSH available
EXPOSE 22

# This is required for sharing Xauthority
ENV QT_X11_NO_MITSHM=1

# Switch to user's HOME folder
WORKDIR /home/${user}

# Using the "exec" form for the Entrypoint command
ENTRYPOINT ["./entrypoint.sh", "terminator"]
#CMD ["-e", "/usr/bin/zsh"]