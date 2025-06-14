# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 17:40:21 by bhajili           #+#    #+#              #
#    Updated: 2025/06/14 21:09:50 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_DIR     = ./objs
LEXER_DIR   = ../srcs/lexer
LIBFT_DIR   = ../libft
LIBFT       = $(LIBFT_DIR)/libft.a

# Files
NAME        = lexer_tester

SRC         = lexer_tester.c \
              basic_tests.c \
              dollar_tests.c \
              quoting_tests.c \
              invalid_quoting_tests.c \
              redirection_tests.c

# Object file paths
OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)
LEXER_OBJ   = $(wildcard $(LEXER_DIR)/objs/*.o)

# Compiler & flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# Default rule
all: $(LIBFT) lexer_objs $(OBJ) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

lexer_objs:
	$(MAKE) -C $(LEXER_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(wildcard $(LEXER_DIR)/objs/*.o) $(LIBFT)

run: all
	./$(NAME)

lexer_test: run

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LEXER_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LEXER_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all run lexer_test clean fclean re lexer_objs