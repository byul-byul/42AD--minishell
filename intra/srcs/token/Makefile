# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/15 13:41:06 by bhajili           #+#    #+#              #
#    Updated: 2025/07/02 15:01:47 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR     = .
OBJ_DIR     = ./objs
LIBFT_DIR   = ../../libft

# Sources & Objects
SRCS        = token_utils_00.c \
              token_utils_01.c \
              token_utils_02.c \
              token_utils_03.c \
              token_utils_04.c

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Rules
all: dependencies $(OBJ_DIR) $(OBJS)

# Compile token source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# Build dependencies
dependencies:
	$(MAKE) -C $(LIBFT_DIR)

# Clean only token objs
clean:
	rm -rf $(OBJ_DIR)

# Clean token + dependencies
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re dependencies