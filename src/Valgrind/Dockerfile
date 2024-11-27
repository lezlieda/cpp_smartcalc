FROM ubuntu:22.04

RUN apt-get -y update; apt-get -y install valgrind; apt-get -y install libgtest-dev; apt-get -y install g++; apt-get -y install make; mkdir -p /usr/src/

WORKDIR /usr/src/

COPY ./src /usr/src/
COPY ./src/Valgrind/start.sh /usr/src

USER root

ENTRYPOINT ["/bin/bash", "start.sh"]

