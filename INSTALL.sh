#!/bin/bash

source CONFIG.sh

# Remove the directory if it already exists
if [ -d "$CMAKE_BUILD_DIRECTORY" ]; then
    echo "Directory '$CMAKE_BUILD_DIRECTORY' already exists..Removing it."
    rm -rf "$CMAKE_BUILD_DIRECTORY"
fi

# Create cmake build directory
mkdir -p "$CMAKE_BUILD_DIRECTORY"

# Create the directory
if [ $? -eq 0 ]; then
    echo "Directory '$CMAKE_BUILD_DIRECTORY' created successfully."
fi

# Change to server directory and run cmake command
echo "Building $APP_NAME......"
cd "$CMAKE_BUILD_DIRECTORY"
cmake -D APP_NAME=$APP_NAME ..
make

cd "$PROJECT_DIRECTORY"

# Remove the bin directory if it already exists
if [ -d "$BINARY_PATH" ]; then
    echo "Directory 'BINARY_PATH' already exists..Removing it."
    rm -rf "$BINARY_PATH"
fi

# Create bin directory
mkdir -p "$BINARY_PATH"

# Copy the binaries to bin directory
cp "$CMAKE_BUILD_DIRECTORY"/"${APP_NAME}App" "$BINARY_PATH"/

# Remove the lib directory if it already exists
if [ -d "$LIBRARY_PATH" ]; then
    echo "Directory 'LIBRARY_PATH' already exists..Removing it."
    rm -rf "$LIBRARY_PATH"
fi

# Create bin directory
mkdir -p "$LIBRARY_PATH"

cp "$CMAKE_BUILD_DIRECTORY"/"lib${APP_NAME}lib.a" "$LIBRARY_PATH"/
