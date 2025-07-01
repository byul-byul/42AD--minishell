# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/24 21:55:36 by bhajili           #+#    #+#              #
#    Updated: 2025/07/01 02:49:02 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR        = .
OBJ_DIR        = ./objs
AST_DIR        = ../ast
EXPANDER_DIR   = ../expander
UTILS_DIR      = ../utils

AST_OBJ_DIR  = $(AST_DIR)/objs
EXPANDER_OBJ_DIR    = $(EXPANDER_DIR)/objs

# Sources & Objects
SRCS    = parser.c \
          parse_command.c \
          parse_redir.c \
          parser_utils_00.c

OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Rules
all: dependencies $(OBJ_DIR) $(OBJS)

# Compile parser source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(AST_DIR) -I$(EXPANDER_DIR) -I$(UTILS_DIR) -c $< -o $@

# Build dependencies
dependencies:
	$(MAKE) -C $(AST_DIR)
	$(MAKE) -C $(EXPANDER_DIR)
	$(MAKE) -C $(UTILS_DIR)

# Clean only parser objs
clean:
	rm -rf $(OBJ_DIR)

# Clean parser + dependencies
fclean: clean
	$(MAKE) -C $(AST_DIR) fclean
	$(MAKE) -C $(EXPANDER_DIR) fclean
	$(MAKE) -C $(UTILS_DIR) fclean

re: fclean all

.PHONY: all clean fclean re dependencies