# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 13:33:47 by bhajili           #+#    #+#              #
#    Updated: 2025/06/18 19:47:03 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR        = .
OBJ_DIR        = ./objs
TOKEN_DIR      = ../token
TOKEN_OBJ_DIR  = $(TOKEN_DIR)/objs

# Sources & Objects
SRCS    = lexer.c
OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Default rule
all: token_objs $(OBJ_DIR) $(OBJS)

# Compile lexer source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(TOKEN_DIR) -c $< -o $@

# Build token_utils
token_objs:
	$(MAKE) -C $(TOKEN_DIR)

# Clean only lexer objs
clean:
	rm -rf $(OBJ_DIR)

# Clean lexer + token
fclean: clean
	$(MAKE) -C $(TOKEN_DIR) fclean

re: fclean all

.PHONY: all clean fclean re token_objs
