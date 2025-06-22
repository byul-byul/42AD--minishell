# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 17:40:21 by bhajili           #+#    #+#              #
#    Updated: 2025/06/22 21:30:02 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
LIBFT_DIR       = ../libft
TOKEN_DIR       = ../srcs/token
LEXER_DIR       = ../srcs/lexer
EXPANDER_DIR    = ../srcs/expander
PARSER_DIR      = ../srcs/parser
ENV_DIR         = ../srcs/env

LIBFT               = $(LIBFT_DIR)/libft.a

OBJ_DIR             = ./objs
TOKEN_OBJ_DIR       = $(TOKEN_DIR)/objs
LEXER_OBJ_DIR       = $(LEXER_DIR)/objs
EXPANDER_OBJ_DIR    = $(EXPANDER_DIR)/objs
PARSER_OBJ_DIR      = $(PARSER_DIR)/objs
ENV_OBJ_DIR         = $(ENV_DIR)/objs

# Testers
LEXER_TESTER_NAME     = lexer_tester
EXPANDER_TESTER_NAME  = expander_tester
PARSER_TESTER_NAME    = parser_tester
ENV_TESTER_NAME       = env_tester

# Test files
COMMON_TEST_SRCS = basic_tests.c \
                   dollar_tests.c \
                   quoting_tests.c \
                   invalid_quoting_tests.c \
                   redirection_tests.c

LEXER_ONLY_SRCS    = lexer_tester.c
EXPANDER_ONLY_SRCS = expander_tester.c
PARSER_ONLY_SRCS   = parser_tester.c
ENV_ONLY_SRCS      = env_tester.c

# Combine
LEXER_TEST_SRCS    = $(LEXER_ONLY_SRCS) $(COMMON_TEST_SRCS)
EXPANDER_TEST_SRCS = $(EXPANDER_ONLY_SRCS) $(COMMON_TEST_SRCS)
PARSER_TEST_SRCS   = $(PARSER_ONLY_SRCS) $(COMMON_TEST_SRCS)
ENV_TEST_SRCS      = $(ENV_ONLY_SRCS)

# Object file paths
LEXER_OBJS    = $(LEXER_TEST_SRCS:%.c=$(OBJ_DIR)/%.o)
EXPANDER_OBJS = $(EXPANDER_TEST_SRCS:%.c=$(OBJ_DIR)/%.o)
PARSER_OBJS   = $(PARSER_TEST_SRCS:%.c=$(OBJ_DIR)/%.o)
ENV_OBJS      = $(ENV_TEST_SRCS:%.c=$(OBJ_DIR)/%.o)

TOKEN_MODULE_OBJS    = $(wildcard $(TOKEN_OBJ_DIR)/*.o)
LEXER_MODULE_OBJS    = $(wildcard $(LEXER_OBJ_DIR)/*.o)
EXPANDER_MODULE_OBJS = $(wildcard $(EXPANDER_OBJ_DIR)/*.o)
PARSER_MODULE_OBJS   = $(wildcard $(PARSER_OBJ_DIR)/*.o)
ENV_MODULE_OBJS      = $(wildcard $(ENV_OBJ_DIR)/*.o)

# Compiler
CC        = cc
CFLAGS    = -Wall -Wextra -Werror -g
RM        = rm -f

# Default rule
all: lexer_test expander_test parser_test

# Compile object files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

token_objs:
	$(MAKE) -C $(TOKEN_DIR)

lexer_objs:
	$(MAKE) -C $(LEXER_DIR)

expander_objs:
	$(MAKE) -C $(EXPANDER_DIR)

parser_objs:
	$(MAKE) -C $(PARSER_DIR)

env_objs:
	$(MAKE) -C $(ENV_DIR)

# Link binaries
$(LEXER_TESTER_NAME): $(LEXER_OBJS) lexer_objs token_objs $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(LEXER_OBJS) $(LEXER_MODULE_OBJS) $(TOKEN_MODULE_OBJS) $(LIBFT)

$(EXPANDER_TESTER_NAME): $(EXPANDER_OBJS) expander_objs lexer_objs token_objs $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(EXPANDER_OBJS) $(EXPANDER_MODULE_OBJS) $(LEXER_MODULE_OBJS) $(TOKEN_MODULE_OBJS) $(LIBFT)

$(PARSER_TESTER_NAME): $(PARSER_OBJS) parser_objs expander_objs lexer_objs token_objs $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(PARSER_OBJS) $(PARSER_MODULE_OBJS) $(EXPANDER_MODULE_OBJS) $(LEXER_MODULE_OBJS) $(TOKEN_MODULE_OBJS) $(LIBFT)

$(ENV_TESTER_NAME): $(ENV_OBJS) env_objs $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(ENV_OBJS) $(ENV_MODULE_OBJS) $(LIBFT)

# Run
lexer_test: $(LEXER_TESTER_NAME)
	./$(LEXER_TESTER_NAME)

expander_test: $(EXPANDER_TESTER_NAME)
	./$(EXPANDER_TESTER_NAME)

parser_test: $(PARSER_TESTER_NAME)
	./$(PARSER_TESTER_NAME)

env_test: $(ENV_TESTER_NAME)
	./$(ENV_TESTER_NAME)

# Clean
clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(TOKEN_DIR) clean
	$(MAKE) -C $(LEXER_DIR) clean
	$(MAKE) -C $(EXPANDER_DIR) clean
	$(MAKE) -C $(PARSER_DIR) clean
	$(MAKE) -C $(ENV_DIR) clean

fclean: clean
	$(RM) \
	$(LIBFT) \
	$(LEXER_TESTER_NAME) \
	$(EXPANDER_TESTER_NAME) \
	$(PARSER_TESTER_NAME) \
	$(ENV_TESTER_NAME)

re: fclean all

.PHONY: all clean fclean re lexer_test expander_test lexer_objs expander_objs token_objs parser_test parser_objs
