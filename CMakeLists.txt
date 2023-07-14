cmake_minimum_required(VERSION 3.25)
project(NekoGL)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)

add_library(NekoGL include/canvas.h src/canvas.cpp src/space3d.cpp include/space3d.h include/vectors.h src/vectors.cpp include/neko_math.h)
target_include_directories(NekoGL PUBLIC include)

add_executable(NekoGLTest example/main.cpp example/architecture/general/math.cpp)
target_include_directories(NekoGLTest PUBLIC include ${SDL2_INCLUDE_DIRS})
target_link_libraries(NekoGLTest NekoGL ${SDL2_LIBRARIES})