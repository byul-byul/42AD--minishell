# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/15 17:40:21 by bhajili           #+#    #+#              #
#    Updated: 2025/06/14 02:52:47 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g -I../incls

LIBFT_DIR			=	 ../libft

LIBFT_A				=	 $(LIBFT_DIR)/libft.a

LEXER_DIR			= 	../srcs/lexer
LEXER_TESTER_SRC	=	lexer_tester.c
LEXER_TESTER_BIN	=	lexer_test

PARSER_DIR			= 	../srcs/parser
PARSER_TESTER_SRC	=	parser_tester.c
PARSER_TESTER_BIN	=	parser_test

LEXER_OBJS			=	$(LEXER_DIR)/objs/lexer.o \
						$(LEXER_DIR)/objs/fetch_token.o \
						$(LEXER_DIR)/objs/extract_token_value.o \
						$(LEXER_DIR)/objs/expand_token_value.o \
						$(LEXER_DIR)/objs/lexer_utils.o

PARSER_OBJS			=	$(PARSER_DIR)/objs/parser.o \
						$(PARSER_DIR)/objs/parser_utils.o

all: lexer_test

lexer_test: $(LIBFT_A) $(LEXER_OBJS)
	$(CC) $(CFLAGS) $(LEXER_OBJS) $(LEXER_TESTER_SRC) $(LIBFT_A) -o $(LEXER_TESTER_BIN)
	./$(LEXER_TESTER_BIN)
	rm -f $(LEXER_TESTER_BIN)

parser_test: $(LIBFT_A) $(LEXER_OBJS) $(PARSER_OBJS)
	$(CC) $(CFLAGS) $(LEXER_OBJS) $(PARSER_OBJS) $(PARSER_TESTER_SRC) $(LIBFT_A) -o $(PARSER_TESTER_BIN)
	./$(PARSER_TESTER_BIN)
	rm -f $(PARSER_TESTER_BIN)

$(LIBFT_A):
	@$(MAKE) -C $(LIBFT_DIR)

$(LEXER_OBJS):
	@$(MAKE) -C $(LEXER_DIR)

$(PARSER_OBJS):
	@$(MAKE) -C $(LEXER_DIR)
	@$(MAKE) -C $(PARSER_DIR)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(LEXER_DIR) clean
	@$(MAKE) -C $(PARSER_DIR) clean

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(LEXER_DIR) fclean
	@$(MAKE) -C $(PARSER_DIR) fclean
	rm -rf $(LEXER_TESTER_BIN)
	rm -rf $(PARSER_TESTER_BIN)

re: fclean all

.PHONY: all clean fclean re lexer_test parser_test
