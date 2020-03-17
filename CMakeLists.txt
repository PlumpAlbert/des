cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(des)

file(GLOB SOURCES "*.h" "*.c")

add_executable(${PROJECT_NAME} ${SOURCES})