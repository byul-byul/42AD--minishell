# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/25 10:36:41 by bhajili           #+#    #+#              #
#    Updated: 2025/06/15 22:13:57 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

D_HDR	=	./
D_SRC	=	./
D_OBJ	=	objs/

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I $(D_HDR)

SRCS	=	$(D_SRC)ft_arr_00.c \
			$(D_SRC)ft_is_00.c \
			$(D_SRC)ft_is_01.c \
			$(D_SRC)ft_is_02.c \
			$(D_SRC)ft_is_03.c \
			$(D_SRC)ft_is_04.c \
			$(D_SRC)ft_is_05.c \
			$(D_SRC)ft_mem_00.c \
			$(D_SRC)ft_mem_01.c \
			$(D_SRC)ft_num_00.c \
			$(D_SRC)ft_put_00.c \
			$(D_SRC)ft_put_01.c \
			$(D_SRC)ft_put_02.c \
			$(D_SRC)ft_to_00.c \
			$(D_SRC)ft_to_01.c \
			$(D_SRC)ft_str_00.c \
			$(D_SRC)ft_str_01.c \
			$(D_SRC)ft_str_02.c \
			$(D_SRC)ft_str_03.c \
			$(D_SRC)ft_str_04.c \
			$(D_SRC)ft_str_05.c \
			$(D_SRC)ft_str_06.c \
			$(D_SRC)ft_str_07.c \
			$(D_SRC)ft_lst_00.c \
			$(D_SRC)ft_lst_01.c \
			$(D_SRC)ft_gnl_00.c \
			$(D_SRC)ft_printf_00.c \
			$(D_SRC)ft_printf_01.c \
			$(D_SRC)ft_printf_02.c \
			$(D_SRC)ft_printf_03.c

OBJS	=	$(SRCS:$(D_SRC)%.c=$(D_OBJ)%.o)

all: $(NAME)

$(D_OBJ)%.o: $(D_SRC)%.c
	@mkdir -p $(D_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	rm -rf $(D_OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re