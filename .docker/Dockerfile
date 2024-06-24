FROM ubuntu:22.04
ENV DEBIAN_FRONTEND noninteractive
ENV CMakeVersion="3.28.2" 
RUN apt-get update  -y
RUN apt-get install -y \
        git \
        build-essential \
        wget \
        g++ \
        gcc \
        pkg-config \
        libssl-dev \
        systemctl \
        net-tools \
        iproute2 \
        nano

RUN mkdir -p /root/toolchains
WORKDIR /root/toolchains
# install CMake
RUN wget https://github.com/Kitware/CMake/releases/download/v$CMakeVersion/cmake-$CMakeVersion-linux-x86_64.tar.gz -P /root/toolchains/cmake
RUN tar xf /root/toolchains/cmake/cmake-$CMakeVersion-linux-x86_64.tar.gz -C /root/toolchains/cmake --checkpoint=.100
RUN ln -sf /root/toolchains/cmake/cmake-$CMakeVersion-linux-x86_64/bin/* /usr/local/bin
RUN rm -rf /root/toolchains/cmake/cmake-$CMakeVersion-linux-x86_64.tar.gz
# install gstreamer
RUN apt-get install -y libgstreamer1.0-dev 
# create workspace
RUN mkdir -p /root/workspace
WORKDIR /root/workspace
# Keep the container running
CMD ["tail", "-f", "/dev/null"]