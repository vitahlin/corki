FROM centos:latest

RUN yum -y install make && \
    yum -y install wget && \
    yum -y install gcc && \
    yum -y install gcc-c++ && \
    wget https://cmake.org/files/v3.6/cmake-3.6.2.tar.gz && \
    tar xvf cmake-3.6.2.tar.gz && cd cmake-3.6.2 && \
    ./bootstrap && \
    gmake && \
    gmake install 


RUN mkdir /vitah
WORKDIR /vitah/