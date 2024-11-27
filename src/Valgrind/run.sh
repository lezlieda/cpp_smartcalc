#!/bin/bash

cd ../../
docker rmi -f ereva/valgrind/smartcalc_v2
docker build . -t ereva/valgrind/smartcalc_v2 -f src/Valgrind/Dockerfile
docker run --rm ereva/valgrind/smartcalc_v2
