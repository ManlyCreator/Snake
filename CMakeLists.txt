# Minimum CMake
cmake_minimum_required(VERSION 3.25)

# Project Name
project(Snake)

# Project Settings
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

# Sets Compiler
set(CMAKE_CXX_COMPILER em++)

# Compile Executable
add_executable(index main.cpp)
target_link_options(index PRIVATE
  -s USE_WEBGL2=1 
  --preload-file ${CMAKE_SOURCE_DIR}/shaders@/shaders
  --shell-file ${CMAKE_SOURCE_DIR}/shellFile.html
)
set(CMAKE_EXECUTABLE_SUFFIX ".html")

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
target_compile_definitions(index PUBLIC PROJECT="${PROJECT_NAME}")

# Links Libraries
target_link_libraries(index PRIVATE glfw3 glm GL m ${Dependencies})
