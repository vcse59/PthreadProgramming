cmake_minimum_required(VERSION 3.10.0)
project(threadlib VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

# Include source code include directories
include_directories(include)

# Define a variable for the executable name
set(APP_NAME "pthread" CACHE STRING "Name of the executable")
set(EXECUTABLE_NAME   "${APP_NAME}App")
set(LIBRARY_NAME      "${APP_NAME}lib")

# Specify the source files
file(GLOB SOURCES CONFIGURE_DEPENDS "src/AppData/*" "src/CommonServices/*" "src/ProducerClass/*" "src/ConsumerClass/*" "src/DebugThread/*")

# Generate library
add_library(${LIBRARY_NAME} ${SOURCES})

#Generate executable
add_executable(${EXECUTABLE_NAME} src/main.cpp ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
