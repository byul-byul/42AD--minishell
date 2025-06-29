# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 13:33:47 by bhajili           #+#    #+#              #
#    Updated: 2025/06/29 11:17:50 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR        = .
OBJ_DIR        = ./objs
TOKEN_DIR      = ../token

ENV_OBJ_DIR    = $(TOKEN_DIR)/objs

# Sources & Objects
SRCS    = lexer.c
OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Rules
all: dependencies $(OBJ_DIR) $(OBJS)

# Compile lexer source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(TOKEN_DIR) -c $< -o $@

# Build dependencies
dependencies:
	$(MAKE) -C $(TOKEN_DIR)

# Clean only expander objs
clean:
	rm -rf $(OBJ_DIR)

# Clean expander + dependencies
fclean: clean
	$(MAKE) -C $(TOKEN_DIR) fclean

re: fclean all

.PHONY: all clean fclean re dependencies