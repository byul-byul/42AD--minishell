# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/24 21:55:36 by bhajili           #+#    #+#              #
#    Updated: 2025/06/29 11:20:07 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR        = .
OBJ_DIR        = ./objs
AST_DIR        = ../ast
EXPANDER_DIR   = ../expander

AST_OBJ_DIR  = $(AST_DIR)/objs
EXPANDER_OBJ_DIR    = $(EXPANDER_DIR)/objs

# Sources & Objects
SRCS    = parser.c \
          parser_utils_00.c \
          parser_utils_01.c

OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Rules
all: dependencies $(OBJ_DIR) $(OBJS)

# Compile parser source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(AST_DIR) -I$(EXPANDER_DIR) -c $< -o $@

# Build dependencies
dependencies:
	$(MAKE) -C $(EXPANDER_DIR)
	$(MAKE) -C $(AST_DIR)

# Clean only parser objs
clean:
	rm -rf $(OBJ_DIR)

# Clean parser + dependencies
fclean: clean
	$(MAKE) -C $(AST_DIR) fclean
	$(MAKE) -C $(EXPANDER_DIR) fclean

re: fclean all

.PHONY: all clean fclean re dependencies