# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 09:53:44 by bhajili           #+#    #+#              #
#    Updated: 2025/03/10 10:21:20 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =   minishell

D_HDR   =   ./
D_SRC   =   ./

CC      =   cc
CFLAGS  =   -Wall -Wextra -Werror
LDFLAGS =   -lreadline

SRCS    =   $(D_SRC)main.c \
			$(D_SRC)minishell.c \
			$(D_SRC)lexer.c

OBJS    =   $(SRCS:.c=.o)

all:    $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
