# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/26 13:53:50 by bhajili           #+#    #+#              #
#    Updated: 2025/07/03 04:08:55 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR      = srcs
MAIN_DIR     = $(SRC_DIR)/main
LIBFT        = ./libft/libft.a
INCLUDES     = -I./incls

# Readline utils
RLFLAGS      = -lreadline -lhistory
RLDIR        = -L/opt/vagrant/embedded/lib
RLINC        = -I/opt/vagrant/embedded/include/readline/readline.h

# Compiler flags
include Makefile.inc

# Executable name
NAME         = minishell

# Default rule
all: libft build_modules $(NAME)

# Step 1: Build all modules (includes main)
build_modules:
	@$(MAKE) -C $(MAIN_DIR)

# Step 2: Collect objs AFTER build and link
$(NAME):
	$(eval OBJS = $(shell find $(SRC_DIR) -type f -path "*/objs/*.o"))
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(RLDIR) $(RLINC) $(RLFLAGS) -o $(NAME)

# Step 2: Collect objs AFTER build and link in DEBUG MODE
debug: all
	$(eval OBJS = $(shell find $(SRC_DIR) -type f -path "*/objs/*.o"))
	$(CC) $(CFLAGS) -DPROGRAM_MODE=DEBUG_MODE $(OBJS) $(LIBFT) $(RLDIR) $(RLINC) $(RLFLAGS) -o $(NAME)

# Step 3: libft
libft:
	@$(MAKE) -C libft

# Cleaning
clean:
	@find $(SRC_DIR) -type d -name objs | xargs rm -rf
	@$(MAKE) -C libft fclean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean

re: fclean all

.PHONY: all build_modules clean fclean re libft
