#!/bin/bash
set -e  # Exit immediately on any command failure

cd build
make -j"$(nproc)"
cd ..
./build/FaceDetectionCpp "$@"

