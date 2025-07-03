# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/15 10:49:40 by bhajili           #+#    #+#              #
#    Updated: 2025/07/03 07:02:54 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR         = .
OBJ_DIR         = ./objs
LEXER_DIR       = ../lexer
ENV_DIR         = ../env
SIGNALS_DIR     = ../signals

LEXER_OBJ_DIR   = $(LEXER_DIR)/objs
ENV_OBJ_DIR     = $(ENV_DIR)/objs
SIGNALS_OBJ_DIR = $(SIGNALS_DIR)/objs

# Sources & Objects
SRCS    = expander.c \
          expand_dollar.c \
          expand_wildcard.c

OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Rules
all: dependencies $(OBJ_DIR) $(OBJS)

# Compile expander source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LEXER_DIR) -I$(ENV_DIR) -I$(SIGNALS_DIR) -c $< -o $@

# Build dependencies
dependencies:
	$(MAKE) -C $(ENV_DIR)
	$(MAKE) -C $(LEXER_DIR)
	$(MAKE) -C $(SIGNALS_DIR)

# Clean only expander objs
clean:
	rm -rf $(OBJ_DIR)

# Clean expander + dependencies
fclean: clean
	$(MAKE) -C $(LEXER_DIR) fclean
	$(MAKE) -C $(ENV_DIR) fclean
	$(MAKE) -C $(SIGNALS_DIR) fclean

re: fclean all

.PHONY: all clean fclean re dependencies