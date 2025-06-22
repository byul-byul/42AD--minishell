# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/24 21:55:36 by bhajili           #+#    #+#              #
#    Updated: 2025/06/20 15:42:30 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR		=	.
OBJ_DIR		=	./objs

# Sources & Objects
SRCS		= 	parser.c \
				parser_utils_00.c

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