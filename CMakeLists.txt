cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include_directories(${CMAKE_SOURCE_DIR}/src)

project(gb-emu)

file(GLOB sources src/**.cpp )

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
set(TTF_LIBS SDL2_ttf)

include_directories("/usr/local/include")
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})
#include_directories(gb-emu ${SDL2_INCLUDE_DIRS})

add_executable(gb-emu ${sources})
target_link_libraries(gb-emu ${SDL2_LIBRARY})
target_link_libraries(gb-emu ${SDL2_TTF_LIBRARY})

target_link_libraries(gb-emu ${SDL2_LIBRARIES} )
target_link_libraries(gb-emu ${SDL2_TTF_LIBRARIES})
target_link_libraries(gb-emu ${TTF_LIBS})