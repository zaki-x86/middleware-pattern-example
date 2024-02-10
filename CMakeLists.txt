cmake_minimum_required(VERSION 3.27)

project(middleware-pattern)

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_executable(${PROJECT_NAME} ${SRCS})
