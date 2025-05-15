# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 13:33:47 by bhajili           #+#    #+#              #
#    Updated: 2025/05/15 16:18:33 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler & flags
CC		= 	cc
CFLAGS	= 	-Wall -Wextra -Werror

# Directories
SRC_DIR		=	 .
OBJ_DIR		= 	./objs
LIBFT_DIR	= ../../libft
TESTER_DIR	= ../../tester

# Sources & Objects
SRCS	= 	lexer.c \
			fetch_token.c \
			extract_to_token.c \
			expand_token_value.c \
			lexer_utils.c

OBJS	= 	$(SRCS:%.c=$(OBJ_DIR)/%.o)

# Tester files
TESTER_SRC	=	$(TESTER_DIR)/lexer_tests.c \
				$(TESTER_DIR)/lexer_tester.c

TESTER_BIN	= lexer_test

# Rules
all: $(OBJ_DIR) $(OBJS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Libft
LIBFT_A		= $(LIBFT_DIR)/libft.a

# Testing target
test_lexer: all $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(TESTER_SRC) $(LIBFT_A) -o $(TESTER_BIN)
	./$(TESTER_BIN)
	rm -f $(TESTER_BIN)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(TESTER_BIN)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re test_lexer