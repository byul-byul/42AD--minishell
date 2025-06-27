# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/24 21:55:36 by bhajili           #+#    #+#              #
#    Updated: 2025/06/27 04:30:06 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR        = .
OBJ_DIR        = ./objs
EXPANDER_DIR      = ../expander
EXPANDER_OBJ_DIR  = $(EXPANDER_DIR)/objs

# Sources & Objects
SRCS        = parser.c \
			  parser_utils_00.c \
			  parser_utils_01.c

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Default rule
all: expander_objs $(OBJ_DIR) $(OBJS)

# Compile parser source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(EXPANDER_DIR) -c $< -o $@

# Build expander_objs
expander_objs:
	$(MAKE) -C $(EXPANDER_DIR)

# Clean only parser objs
clean:
	rm -rf $(OBJ_DIR)

# Clean parser + expander
fclean: clean
	$(MAKE) -C $(EXPANDER_DIR) fclean

re: fclean all

.PHONY: all clean fclean re expander_objs
