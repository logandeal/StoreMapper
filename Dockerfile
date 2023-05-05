FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y build-essential git make cmake libgtest-dev
RUN cd /usr/src/gtest && cmake CMakeLists.txt && make && cp *.a /usr/lib
RUN git clone https://github.com/logandeal/StoreMapper.git
RUN cd StoreMapper/src && make
WORKDIR StoreMapper/src
CMD ["./main"]