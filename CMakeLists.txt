cmake_minimium_required (VERSION 3.2)
project(audio-server)

# Setup environment for g++
set(CMAKE_CXX_STANDARD 14) # C++14 standard for Wt
set(CMAKE_CXX_STANDARD_REQUIRED ON) # C++14 required
set(CMAKE_CXX_EXTENSIONS ON) # allow gnu g++ extensions
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra" )#-lwt -lwthttp")

add_executable(AudioServer main.cpp)
set_target_properties(AudioServer
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../bin"
  )
