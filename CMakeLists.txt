cmake_minimum_required (VERSION 3.2)
project(audio-server)

# Setup environment for g++
set(CMAKE_CXX_STANDARD 14) # C++14 standard for Wt
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++14 required
set(CMAKE_CXX_EXTENSIONS ON) # allow gnu g++ extensions
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lsqlite3 -lcryptopp" )#-lwt -lwthttp")

# Need to use some custom Find modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(CryptoPP REQUIRED)

add_executable(AudioServer main.cpp)
set_target_properties(AudioServer
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin"
  )
