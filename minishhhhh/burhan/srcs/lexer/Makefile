# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 13:33:47 by bhajili           #+#    #+#              #
#    Updated: 2025/05/15 17:39:34 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Directories
SRC_DIR		=	.
OBJ_DIR		=	./objs

# Sources & Objects
SRCS		= 	lexer.c \
				fetch_token.c \
				extract_to_token.c \
				expand_token_value.c \
				lexer_utils.c

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