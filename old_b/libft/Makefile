# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/25 10:36:41 by bhajili           #+#    #+#              #
#    Updated: 2024/12/26 13:42:22 by bhajili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

D_HDR	=	./
D_SRC	=	./

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	$(D_SRC)ft_arr_00.c \
			$(D_SRC)ft_is_00.c \
			$(D_SRC)ft_is_01.c \
			$(D_SRC)ft_is_02.c \
			$(D_SRC)ft_is_03.c \
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

OBJS	=	${SRCS:.c=.o}
			
all: ${NAME}

%.o	:	%.c
	$(CC) $(CFLAGS) -c $< -o $@	-I $(D_HDR)

${NAME}: ${OBJS}
	ar rcs ${NAME} ${OBJS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY:	all clean fclean re