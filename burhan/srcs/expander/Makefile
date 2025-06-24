# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/15 10:49:40 by bhajili           #+#    #+#              #
#    Updated: 2025/06/23 21:05:43 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR        = .
OBJ_DIR        = ./objs
LEXER_DIR      = ../lexer
LEXER_OBJ_DIR  = $(LEXER_DIR)/objs

# Sources & Objects
SRCS    = expander_00.c \
          expander_01.c

OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Rules
all: lexer_objs $(OBJ_DIR) $(OBJS)

# Compile lexer source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LEXER_DIR) -c $< -o $@

# Build lexer_utils
lexer_objs:
	$(MAKE) -C $(LEXER_DIR)

# Clean only expander objs
clean:
	rm -rf $(OBJ_DIR)

# Clean expander + lexer
fclean: clean
	$(MAKE) -C $(LEXER_DIR) fclean

re: fclean all

.PHONY: all clean fclean re lexer_objs