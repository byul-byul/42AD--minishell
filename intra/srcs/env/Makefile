# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/22 20:08:31 by bhajili           #+#    #+#              #
#    Updated: 2025/06/29 11:29:24 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR     = .
OBJ_DIR     = ./objs
LIBFT_DIR   = ../../libft

# Sources & Objects
SRCS        = env_utils_00.c \
              env_utils_01.c \
              env_utils_02.c

OBJS        = $(SRCS:%.c=$(OBJ_DIR)/%.o)

# Include shared flags (optional)
include ../../Makefile.inc

# Rules
all: dependencies $(OBJ_DIR) $(OBJS)

# Compile env source files
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

# Build dependencies
dependencies:
	$(MAKE) -C $(LIBFT_DIR)

# Clean only env objs
clean:
	rm -rf $(OBJ_DIR)

# Clean env + dependencies
fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re dependencies