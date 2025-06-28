# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 09:53:44 by bhajili           #+#    #+#              #
#    Updated: 2025/06/28 14:11:44 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR         = .
OBJ_DIR         = ./objs
ENV_DIR         = ../env
PARSER_DIR      = ../parser
SIGNALS_DIR     = ../signals

ENV_OBJ_DIR     = $(ENV_DIR)/objs
PARSER_OBJ_DIR  = $(PARSER_DIR)/objs
SIGNALS_OBJ_DIR = $(SIGNALS_DIR)/objs

# Sources & Objects
SRCS        = exec_manager.c \
              exec_command.c \
              exec_builtin_00.c \
              exec_builtin_01.c \
			  exec_external_00.c \
			  exec_pipe.c

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Default rule
all: deps $(OBJ_DIR) $(OBJS)

# Compile exec source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(ENV_DIR) -I$(PARSER_DIR) -I$(SIGNALS_DIR) -c $< -o $@

# Build dependencies
deps:
	$(MAKE) -C $(ENV_DIR)
	$(MAKE) -C $(PARSER_DIR)
	$(MAKE) -C $(SIGNALS_DIR)

# Clean only exec objs
clean:
	rm -rf $(OBJ_DIR)

# Clean exec + dependencies
fclean: clean
	$(MAKE) -C $(ENV_DIR) fclean
	$(MAKE) -C $(PARSER_DIR) fclean
	$(MAKE) -C $(SIGNALS_DIR) fclean

re: fclean all

.PHONY: all clean fclean re deps
