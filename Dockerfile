FROM ubuntu:16.04
RUN apt-get update
RUN apt-get install -y g++
RUN mkdir -p /exec
COPY main.cpp /exec/main.cpp
RUN g++ -O3 -std=c++14 -o /exec/main /exec/main.cpp
ENTRYPOINT ["/exec/main"]