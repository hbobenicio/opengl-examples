cmake_minimum_required(VERSION 2.8)
project(hello-world)

find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
#find_package(GLEW REQUIRED)
#find_package(GLM REQUIRED)
find_package(SDL2 REQUIRED)

#INCLUDE(FindPkgConfig)
#PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
#PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

execute_process(COMMAND sdl2-config --cflags  OUTPUT_VARIABLE SDL2_FLAGS   OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND sdl2-config --libs    OUTPUT_VARIABLE SDL2_LIBS    OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND sdl2-config --version OUTPUT_VARIABLE SDL2_VERSION OUTPUT_STRIP_TRAILING_WHITESPACE)
message("SDL2_VERSION: ${SDL2_VERSION}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -std=c++14 ${SDL2_FLAGS}")

add_executable(hello-world hello-world.cpp)
add_library(sdl2-wrapper STATIC IMPORTED)
set_property(TARGET sdl2-wrapper PROPERTY IMPORTED_LOCATION "/home/hugo/projetos/sdl2/sdl2-wrapper/sdl2-wrapper.o")
include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${GLUT_INCLUDE_DIRS}
    ${GLEW_INCLUDE_DIR}
    "/home/hugo/projetos/sdl2/sdl2-wrapper"
)
target_link_libraries(hello-world
    sdl2-wrapper
    ${OPENGL_LIBRARIES}
    ${GLUT_LIBRARY}
    ${GLEW_LIBRARY}
    ${SDL2_LIBS}
)
