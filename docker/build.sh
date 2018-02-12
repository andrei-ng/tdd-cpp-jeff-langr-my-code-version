#!/usr/bin/env bash

# Check args
if [ "$#" -ne 2 ]; then
  echo "usage: ./build.sh TARGET_PLATFORM_NAME IMAGE_NAME"
  exit 1
fi

TARGET_PLATFORM_NAME=$1
IMAGE_NAME=$2

# Set custom arguments
dUSER=docker
dSHELL=/usr/bin/zsh

# Copy custom config files
cp -r configs $TARGET_PLATFORM_NAME/configs
# Copy custom entrypoint script
cp entrypoint.sh $TARGET_PLATFORM_NAME/entrypoint.sh
# Copy my GTest CMake example
cp -r ../gtest_cmake_module_based_example $TARGET_PLATFORM_NAME/gtest_cmake_module_based_example

# Build the docker image
docker build \
  --build-arg user=$dUSER\
  --build-arg uid=$UID\
  --build-arg shell=$dSHELL\
  -t $IMAGE_NAME $TARGET_PLATFORM_NAME


# Clean up
# Remove configs folder
rm -rf $TARGET_PLATFORM_NAME/configs
# Remove copied script
rm -rf $TARGET_PLATFORM_NAME/entrypoint.sh
# Remove the example from the Docker build folder
rm -rf $TARGET_PLATFORM_NAME/gtest_cmake_module_based_example



