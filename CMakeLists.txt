# Minimum CMake
cmake_minimum_required(VERSION 3.25)

# Project Name
project(Snake)

# Project Settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Sets Compiler
set(CMAKE_CXX_COMPILER g++)

# Compile Executable
add_executable(Snake main.cpp)
set(CMAKE_CXX_FLAGS "-std=c++11")

# Compile Libraries
set(Dependencies)

function(create_library library src libraryList)
  add_library(${library} STATIC ${src})
  list(APPEND ${libraryList} ${library})
  return(PROPAGATE ${libraryList})
endfunction()

create_library(Shader src/shader.cpp Dependencies)
create_library(Shape src/shape.cpp Dependencies)
create_library(Cube src/cube.cpp Dependencies)
create_library(Torus src/torus.cpp Dependencies)
create_library(Camera src/camera.cpp Dependencies)

# Include Directory
include_directories(/usr/local/include/ include/)

# Creates a PROJECT Macro
target_compile_definitions(${PROJECT_NAME} PUBLIC PROJECT="${PROJECT_NAME}")

# Links Libraries
target_link_libraries(${PROJECT_NAME} PRIVATE glfw3 GL m ${Dependencies})
