cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

project(des)

file(GLOB SOURCES "include/*/*.h" "include/*/*.c" "src/*.c")
message(Sources: ${SOURCES})
include_directories(AFTER SYSTEM "include")
add_executable(${PROJECT_NAME} ${SOURCES})