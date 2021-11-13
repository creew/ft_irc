cmake_minimum_required(VERSION 3.20)
project(ft_irc)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_irc src/main.cpp
        src/Server.cpp src/Server.h
        src/ServerConfiguration.cpp src/ServerConfiguration.h
        src/CommandProcessor.cpp src/CommandProcessor.h)
