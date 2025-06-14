# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 17:40:21 by bhajili           #+#    #+#              #
#    Updated: 2025/06/14 17:09:03 by bhajili          ###   ########.fr        #
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
			  invalid_quoting_tests.c

LEXER_SRC   = $(LEXER_DIR)/lexer.c \
              $(LEXER_DIR)/fetch_token.c \
              $(LEXER_DIR)/extract_token_value.c \
              $(LEXER_DIR)/expand_token_value.c \
              $(LEXER_DIR)/lexer_utils.c

# Object file paths
OBJ         = $(SRC:%.c=$(OBJ_DIR)/%.o)
LEXER_OBJ   = $(LEXER_SRC:$(LEXER_DIR)/%.c=$(LEXER_DIR)/objs/%.o)

# Compiler & flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
RM          = rm -f

# Default rule
all: $(LIBFT) $(LEXER_OBJ) $(OBJ) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(LEXER_OBJ):
	$(MAKE) -C $(LEXER_DIR)

$(NAME): $(OBJ) $(LEXER_OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LEXER_OBJ) $(LIBFT)

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

.PHONY: all run lexer_test clean fclean re

# NAME        = lexer_tester
# LEXER_DIR   = ../srcs/lexer
# LIBFT_DIR   = ../libft
# LIBFT       = $(LIBFT_DIR)/libft.a

# SRC         = lexer_tester.c \
#               $(LEXER_DIR)/lexer.c \
#               $(LEXER_DIR)/fetch_token.c \
#               $(LEXER_DIR)/extract_token_value.c \
#               $(LEXER_DIR)/expand_token_value.c \
#               $(LEXER_DIR)/lexer_utils.c

# OBJ         = $(SRC:.c=.o)

# CC          = cc
# CFLAGS      = -Wall -Wextra -Werror
# RM          = rm -f

# # Default rule
# all: $(LIBFT) $(NAME)

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR)

# $(NAME): $(SRC) $(LIBFT)
# 	$(CC) $(CFLAGS) -o $(NAME) $(SRC) $(LIBFT)

# run: all
# 	./$(NAME)

# lexer_test: run

# lexer_basic: all
# 	./$(NAME) | awk '/=== BASIC TOKEN TESTS ===/,/^===/ { print }'

# lexer_dollar: all
# 	./$(NAME) | awk '/=== DOLLAR EXPANSION TESTS ===/,/^===/ { print }'

# lexer_quoting: all
# 	./$(NAME) | awk '/=== QUOTING TESTS ===/,/^===/ { print }'

# lexer_redirects: all
# 	./$(NAME) | awk '/=== REDIRECTS ===/,/^===/ { print }'

# lexer_heredoc: all
# 	./$(NAME) | awk '/=== HEREDOC + EXPAND ===/,/^===/ { print }'

# lexer_pipes: all
# 	./$(NAME) | awk '/=== PIPES & LOGICALS ===/,/^===/ { print }'

# lexer_parens: all
# 	./$(NAME) | awk '/=== PARENTHESIS ===/,/^===/ { print }'

# lexer_edge: all
# 	./$(NAME) | awk '/=== EDGE CASES ===/,/^===/ { print }'

# clean:
# 	$(RM) $(NAME) *.o
# 	$(MAKE) -C $(LIBFT_DIR) clean

# fclean: clean
# 	$(MAKE) -C $(LIBFT_DIR) fclean

# re: fclean all

# .PHONY: all run lexer_test lexer_basic lexer_dollar lexer_quoting lexer_redirects lexer_heredoc lexer_pipes lexer_parens lexer_edge clean fclean re


# CC					=	cc
# CFLAGS				=	-Wall -Wextra -Werror -g -I../incls

# LIBFT_DIR			=	 ../libft

# LIBFT_A				=	 $(LIBFT_DIR)/libft.a

# LEXER_DIR			= 	../srcs/lexer
# LEXER_TESTER_SRC	=	lexer_tester.c
# LEXER_TESTER_BIN	=	lexer_test

# PARSER_DIR			= 	../srcs/parser
# PARSER_TESTER_SRC	=	parser_tester.c
# PARSER_TESTER_BIN	=	parser_test

# LEXER_OBJS			=	$(LEXER_DIR)/objs/lexer.o \
# 						$(LEXER_DIR)/objs/fetch_token.o \
# 						$(LEXER_DIR)/objs/extract_token_value.o \
# 						$(LEXER_DIR)/objs/expand_token_value.o \
# 						$(LEXER_DIR)/objs/lexer_utils.o

# PARSER_OBJS			=	$(PARSER_DIR)/objs/parser.o \
# 						$(PARSER_DIR)/objs/parser_utils.o

# all: lexer_test

# lexer_test: $(LIBFT_A) $(LEXER_OBJS)
# 	$(CC) $(CFLAGS) $(LEXER_OBJS) $(LEXER_TESTER_SRC) $(LIBFT_A) -o $(LEXER_TESTER_BIN)
# 	./$(LEXER_TESTER_BIN)
# 	rm -f $(LEXER_TESTER_BIN)

# parser_test: $(LIBFT_A) $(LEXER_OBJS) $(PARSER_OBJS)
# 	$(CC) $(CFLAGS) $(LEXER_OBJS) $(PARSER_OBJS) $(PARSER_TESTER_SRC) $(LIBFT_A) -o $(PARSER_TESTER_BIN)
# 	./$(PARSER_TESTER_BIN)
# 	rm -f $(PARSER_TESTER_BIN)

# $(LIBFT_A):
# 	@$(MAKE) -C $(LIBFT_DIR)

# $(LEXER_OBJS):
# 	@$(MAKE) -C $(LEXER_DIR)

# $(PARSER_OBJS):
# 	@$(MAKE) -C $(LEXER_DIR)
# 	@$(MAKE) -C $(PARSER_DIR)

# clean:
# 	@$(MAKE) -C $(LIBFT_DIR) clean
# 	@$(MAKE) -C $(LEXER_DIR) clean
# 	@$(MAKE) -C $(PARSER_DIR) clean

# fclean: clean
# 	@$(MAKE) -C $(LIBFT_DIR) fclean
# 	@$(MAKE) -C $(LEXER_DIR) fclean
# 	@$(MAKE) -C $(PARSER_DIR) fclean
# 	rm -rf $(LEXER_TESTER_BIN)
# 	rm -rf $(PARSER_TESTER_BIN)

# re: fclean all

# .PHONY: all clean fclean re lexer_test parser_test
