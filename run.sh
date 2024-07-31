#!/bin/bash

pushd .
cd ./tests || exit

cmake -B build ..

if [ $? -ne 0 ]; then
    echo "CMake configuration failed"
    popd
    exit 1
fi

cmake --build build

if [ $? -ne 0 ]; then
    echo "Build failed"
    popd
    exit 1
fi

./build/tests

popd
