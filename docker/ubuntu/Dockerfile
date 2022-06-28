FROM ubuntu:20.04

RUN apt-get update && \
    apt install -y build-essential wget && \
    apt install -y libssl-dev
RUN wget https://cmake.org/files/v3.21/cmake-3.21.1.tar.gz && \
    tar xvf cmake-3.21.1.tar.gz && cd cmake-3.21.1 && \
    ./bootstrap && \
    make && \
    make install
RUN mkdir /c
WORKDIR /c