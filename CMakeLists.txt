cmake_minimum_required(VERSION 3.10.0)
project(threadlib VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Include source code include directories
include_directories(.)

# Specify the source files
file(GLOB SOURCES CONFIGURE_DEPENDS "AppData/*" "CommonServices/*" "ProducerClass/*" "CommonServices/*" "DebugThread/*")

# Generate library
add_library(threadlib ${SOURCES})

#Generate executable
add_library(threadApp main.cpp ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
