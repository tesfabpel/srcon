cmake_minimum_required(VERSION 3.2)
project(srcon)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall ") #-Werror

set(SOURCE_FILES main.c)
add_executable(srcon ${SOURCE_FILES} rcon_packet.h)
