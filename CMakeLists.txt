cmake_minimum_required(VERSION 3.23)
project(Chat C)

set(CMAKE_C_STANDARD 99)

add_executable(Chat
        src/client.c
        src/procedure/pack.c
        src/protocol/udp.c
        src/procedure/unpack.c
        src/protocol/scp.c
        src/protocol/ip.c
        src/protocol/ppp.c
        src/utils/common.h
        )

find_package(Threads REQUIRED)
target_link_libraries(Chat Threads::Threads)
