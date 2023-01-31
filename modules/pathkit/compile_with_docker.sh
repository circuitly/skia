#!/bin/sh
docker build . -t emsdk:latest
docker run \
    --rm \
    -v $(pwd)/../..:/src \
    -u $(id -u):$(id -g) \
    emsdk:latest \
    bash -c "cd /src/modules/pathkit && ./compile.sh"