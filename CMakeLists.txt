cmake_minimum_required(VERSION 3.20)
project(ft_irc)

set(CMAKE_CXX_STANDARD 98)

add_executable(ft_irc src/main.cpp
        src/Server.cpp headers/Server.h
        src/ServerConfiguration.cpp headers/ServerConfiguration.h
        src/CommandProcessor.cpp headers/CommandProcessor.h
        src/Client.cpp headers/Client.h
        src/StringUtils.cpp headers/StringUtils.h
        src/InMessage.cpp headers/InMessage.h
        headers/Errors.h
        src/RawMessage.cpp headers/RawMessage.h
        src/Channel.cpp headers/Channel.h
        headers/commands/ICommand.h
        src/commands/User.cpp headers/commands/User.h
        src/commands/Nick.cpp headers/commands/Nick.h
        src/commands/Ping.cpp headers/commands/Ping.h
        src/commands/Pong.cpp headers/commands/Pong.h
        src/commands/List.cpp headers/commands/List.h
        src/commands/Quit.cpp headers/commands/Quit.h
        src/commands/Pass.cpp headers/commands/Pass.h
        src/commands/CommonReplies.cpp headers/commands/CommonReplies.h src/commands/Join.cpp headers/commands/Join.h src/ChannelHandler.cpp headers/ChannelHandler.h src/commands/Privmsg.cpp headers/commands/Privmsg.h)

include_directories(headers)
set_property(TARGET ft_irc PROPERTY CXX_STANDARD 98)
