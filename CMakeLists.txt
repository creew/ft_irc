cmake_minimum_required(VERSION 3.20)
project(ft_irc)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_irc src/main.cpp
        src/Server.cpp headers/Server.h
        src/ServerConfiguration.cpp headers/ServerConfiguration.h
        src/CommandProcessor.cpp headers/CommandProcessor.h
        src/Client.cpp headers/Client.h
        src/StringUtils.cpp headers/StringUtils.h
        src/Message.cpp headers/Message.h
        src/Errors.cpp headers/Errors.h
        src/OutMessage.cpp headers/OutMessage.h)

include_directories(headers)
set_property(TARGET ft_irc PROPERTY CXX_STANDARD 98)
