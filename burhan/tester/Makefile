# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 17:40:21 by bhajili           #+#    #+#              #
#    Updated: 2025/05/15 20:55:54 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I../libft

LIBFT_DIR	=	 ../libft

LIBFT_A		=	 $(LIBFT_DIR)/libft.a

LEXER_DIR	= 	../srcs/lexer

LEXER_OBJS	=	$(LEXER_DIR)/objs/lexer.o \
				$(LEXER_DIR)/objs/fetch_token.o \
				$(LEXER_DIR)/objs/extract_to_token.o \
				$(LEXER_DIR)/objs/expand_token_value.o \
				$(LEXER_DIR)/objs/lexer_utils.o

LEXER_TESTER_SRC	=	lexer_tester.c
LEXER_TESTER_BIN	=	lexer_test

all: lexer_test

lexer_test: $(LIBFT_A) $(LEXER_OBJS)
	$(CC) $(CFLAGS) $(LEXER_OBJS) $(LEXER_TESTER_SRC) $(LIBFT_A) -o $(LEXER_TESTER_BIN)
	./$(LEXER_TESTER_BIN)
	rm -f $(LEXER_TESTER_BIN)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(LEXER_OBJS):
	@$(MAKE) -C $(LEXER_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(LEXER_DIR) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(LEXER_DIR) fclean

re: fclean all

.PHONY: all clean fclean re lexer_test
