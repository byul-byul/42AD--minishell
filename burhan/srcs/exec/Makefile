# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 09:53:44 by bhajili           #+#    #+#              #
#    Updated: 2025/07/03 07:02:49 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR         = .
OBJ_DIR         = ./objs
ENV_DIR         = ../env
PARSER_DIR      = ../parser

ENV_OBJ_DIR     = $(ENV_DIR)/objs
PARSER_OBJ_DIR  = $(PARSER_DIR)/objs

# Sources & Objects
SRCS        = exec_manager.c \
              exec_command.c \
              exec_builtin_00.c \
              exec_builtin_01.c \
              exec_builtin_02.c \
			  exec_external_00.c \
			  exec_external_01.c \
			  exec_pipe.c \
			  handle_heredoc.c

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Default rule
all: dependencies $(OBJ_DIR) $(OBJS)

# Compile exec source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(ENV_DIR) -I$(PARSER_DIR) -c $< -o $@

# Build dependencies
dependencies:
	$(MAKE) -C $(ENV_DIR)
	$(MAKE) -C $(PARSER_DIR)

# Clean only exec objs
clean:
	rm -rf $(OBJ_DIR)

# Clean exec + dependencies
fclean: clean
	$(MAKE) -C $(ENV_DIR) fclean
	$(MAKE) -C $(PARSER_DIR) fclean

re: fclean all

.PHONY: all clean fclean re dependencies
