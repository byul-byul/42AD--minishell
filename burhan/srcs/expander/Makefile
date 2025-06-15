# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/15 10:49:40 by bhajili           #+#    #+#              #
#    Updated: 2025/06/15 10:49:57 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR		=	.
OBJ_DIR		=	./objs

# Sources & Objects
SRCS		= 	expander.c

OBJS		= 	$(SRCS:%.c=$(OBJ_DIR)/%.o)

include ../../Makefile.inc

# Rules
all: $(OBJ_DIR) $(OBJS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean

re: fclean all

.PHONY: all clean fclean re