# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 09:53:44 by bhajili           #+#    #+#              #
#    Updated: 2025/05/14 23:59:01 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    =   minishell

D_HDR   =   ./incls/
D_SRC   =   ./srcs/

CC      =   cc
CFLAGS  =   -Wall -Wextra -Werror
LDFLAGS =   -lreadline

SRCS    =   $(D_SRC)main.c \
			$(D_SRC)minishell.c \
			$(D_SRC)lexer.c

OBJS    =   $(SRCS:.c=.o)

# Define the targets
all:	$(NAME)

# linking with dependencies on object files
$(NAME): $(OBJS) libft/libft.a
	$(CC) -o $@ $^ -Llibft -lft $(LDFLAGS)

# Library rule to build libft if needed
libft/libft.a:
	make -C libft

clean:
	rm -f $(OBJS)
	make -C libft clean

fclean: clean
	rm -f libft/libft.a $(NAME)

re: fclean all

.PHONY: all libft clean fclean re bonus