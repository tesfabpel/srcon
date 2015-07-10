cmake_minimum_required(VERSION 3.2)
project(srcon)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lreadline -std=c99 -Wall") #-Werror

set(SOURCE_FILES main.c rcon_packet.c)
add_executable(srcon ${SOURCE_FILES} main.h)
