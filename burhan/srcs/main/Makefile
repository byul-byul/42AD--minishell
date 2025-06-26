# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 13:33:47 by bhajili           #+#    #+#              #
#    Updated: 2025/06/26 13:46:39 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR        = .
OBJ_DIR        = ./objs
EXEC_DIR      = ../exec
EXEC_OBJ_DIR  = $(EXEC_DIR)/objs

# Sources & Objects
SRCS        = main.c \
              minishell.c \
			  utils_00.c

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Default rule
all: exec_objs $(OBJ_DIR) $(OBJS)

# Compile main source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(EXEC_DIR) -c $< -o $@

# Build exec_objs
exec_objs:
	$(MAKE) -C $(EXEC_DIR)

# Clean only main objs
clean:
	rm -rf $(OBJ_DIR)

# Clean main + exec
fclean: clean
	$(MAKE) -C $(EXEC_DIR) fclean

re: fclean all

.PHONY: all clean fclean re exec_objs
