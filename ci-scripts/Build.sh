#!/bin/bash

echo "# Create Build Folder"

mkdir build
cd build

echo "# Start Building"

emcmake cmake ../src -DCMAKE_CXX_FLAGS="-O2 -mreference-types"
emmake make -j4
