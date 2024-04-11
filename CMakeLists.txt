cmake_minimum_required(VERSION 3.5)
project(main)

set(CMAKE_C_FLAGS "-std=c11 -Wall -Wextra -Wshadow -Werror")

add_library(graph SHARED src/graph.c)

include_directories(include)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} m graph)





