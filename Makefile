ALL_CPP =	commands/CommonReplies.cpp \
		commands/Invite.cpp \
        commands/Join.cpp \
        commands/Kick.cpp \
        commands/List.cpp \
        commands/Mode.cpp \
        commands/Names.cpp \
        commands/Nick.cpp \
        commands/Notice.cpp \
        commands/Part.cpp \
        commands/Pass.cpp \
        commands/Ping.cpp \
        commands/Pong.cpp \
        commands/Privmsg.cpp \
        commands/Quit.cpp \
        commands/Topic.cpp \
        commands/User.cpp \
        commands/Who.cpp \
        messages/ClientRawMessage.cpp \
        messages/InMessage.cpp \
        messages/RawMessage.cpp \
        messages/ServerRawMessage.cpp \
        Channel.cpp \
        ChannelHandler.cpp \
        ChannelModeHandler.cpp \
        Client.cpp \
        CommandProcessor.cpp \
        main.cpp \
        Server.cpp \
        ServerConfiguration.cpp \
        StringUtils.cpp \
        UserHandler.cpp
SRCDIR = ./src
OBJDIR = ./obj
OBJDIRS = $(OBJDIR) $(OBJDIR)/commands $(OBJDIR)/messages

ALL_OBJ = $(ALL_CPP:%.cpp=%.o)

OBJS = $(addprefix $(OBJDIR)/, $(ALL_OBJ))
DEPENDS = ${OBJS:.o=.d}

FLAGS = -Wall -Wextra -Werror -std=c++98

NAME = ircserv

all: $(NAME)

-include ${DEPENDS}

$(NAME): $(OBJS)
	g++ -o $@ $(FLAGS) $(OBJS)

$(OBJDIRS):
	/bin/mkdir -p $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIRS)
	g++ -o $@ $(FLAGS) -MMD -I./headers -c $<

clean:
	/bin/rm -rf $(OBJDIRS)

fclean: clean
	/bin/rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
