# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 17:40:21 by bhajili           #+#    #+#              #
#    Updated: 2025/06/15 12:38:13 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
OBJ_DIR         = ./objs
LEXER_DIR       = ../srcs/lexer
EXPANDER_DIR    = ../srcs/expander
LIBFT_DIR       = ../libft

LEXER_OBJ_DIR       = $(LEXER_DIR)/objs
EXPANDER_OBJ_DIR    = $(EXPANDER_DIR)/objs

LIBFT           = $(LIBFT_DIR)/libft.a

# Files
LEXER_TESTER_NAME     = lexer_tester
EXPANDER_TESTER_NAME  = expander_tester

# Shared test files
COMMON_TEST_SRCS = basic_tests.c \
                   dollar_tests.c \
                   quoting_tests.c

LEXER_ONLY_SRCS = lexer_tester.c \
                  invalid_quoting_tests.c \
                  redirection_tests.c

EXPANDER_ONLY_SRCS = expander_tester.c

# Combine
LEXER_TEST_SRCS    = $(LEXER_ONLY_SRCS) $(COMMON_TEST_SRCS)
EXPANDER_TEST_SRCS = $(EXPANDER_ONLY_SRCS) $(COMMON_TEST_SRCS)

# Object file paths
LEXER_OBJS    = $(LEXER_TEST_SRCS:%.c=$(OBJ_DIR)/%.o)
EXPANDER_OBJS = $(EXPANDER_TEST_SRCS:%.c=$(OBJ_DIR)/%.o)

LEXER_MODULE_OBJS    = $(wildcard $(LEXER_OBJ_DIR)/*.o)
EXPANDER_MODULE_OBJS = $(wildcard $(EXPANDER_OBJ_DIR)/*.o)

# Compiler
CC        = cc
CFLAGS    = -Wall -Wextra -Werror
RM        = rm -f

# Default rule
all: lexer_test expander_test

# Compile object files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

lexer_objs:
	$(MAKE) -C $(LEXER_DIR)

expander_objs:
	$(MAKE) -C $(EXPANDER_DIR)

# Link binaries
$(LEXER_TESTER_NAME): $(LEXER_OBJS) lexer_objs $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(LEXER_OBJS) $(LEXER_MODULE_OBJS) $(LIBFT)

$(EXPANDER_TESTER_NAME): $(EXPANDER_OBJS) expander_objs lexer_objs $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(EXPANDER_OBJS) $(EXPANDER_MODULE_OBJS) $(LEXER_MODULE_OBJS) $(LIBFT)

# Run
lexer_test: $(LEXER_TESTER_NAME)
	./$(LEXER_TESTER_NAME)

expander_test: $(EXPANDER_TESTER_NAME)
	./$(EXPANDER_TESTER_NAME)

# Clean
clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) -C $(LEXER_DIR) clean
	$(MAKE) -C $(EXPANDER_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(LEXER_TESTER_NAME) $(EXPANDER_TESTER_NAME)
	$(MAKE) -C $(LEXER_DIR) fclean
	$(MAKE) -C $(EXPANDER_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re lexer_test expander_test lexer_objs expander_objs
