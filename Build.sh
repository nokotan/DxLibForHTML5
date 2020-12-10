!/bin/bash

echo "# Create Build Folder"

mkdir build
cd build

echo "# Start Building"

emcmake cmake .. -DCMAKE_CXX_FLAGS="-O2"
emmake make