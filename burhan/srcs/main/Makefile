# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 13:33:47 by bhajili           #+#    #+#              #
#    Updated: 2025/06/29 11:41:56 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR        = .
OBJ_DIR        = ./objs
EXEC_DIR       = ../exec

EXEC_OBJ_DIR  = $(EXEC_DIR)/objs

# Sources & Objects
SRCS    = main.c \
          minishell.c \
          utils_00.c

OBJS    = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Rules
all: dependencies $(OBJ_DIR) $(OBJS)

# Compile core source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(EXEC_DIR) -c $< -o $@

# Build dependencies
dependencies:
	$(MAKE) -C $(EXEC_DIR)

# Clean only core objs
clean:
	rm -rf $(OBJ_DIR)

# Clean core + dependencies
fclean: clean
	$(MAKE) -C $(EXEC_DIR) fclean

re: fclean all

.PHONY: all clean fclean re dependencies