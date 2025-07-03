/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:28:10 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 09:28:17 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	print_space(t_arg *arg, int delta)
{
	if ((((!flag_check(arg, FLAG_ZERO) || arg->prec > -1)
				&& !flag_check(arg, FLAG_DASH)) && !flag_check(arg, FLAG_PRNT))
		|| (flag_check(arg, FLAG_DASH) && flag_check(arg, FLAG_PRNT)))
		arg->res += putchar_len_times(arg->width - delta, ' ');
}

static void	print_zero(t_arg *arg, int delta, int count)
{
	if (flag_check(arg, FLAG_ZERO) && !flag_check(arg, FLAG_DASH)
		&& arg->prec <= -1)
		arg->res += putchar_len_times(arg->width - delta, '0');
	arg->res += putchar_len_times(arg->prec - count, '0');
}

static void	print_sign_and_prefix(t_arg *arg)
{
	if (arg->sign)
		arg->res += putchar_len_times(1, arg->sign);
	if (arg->prefix)
		arg->res += write(1, arg->prefix, ft_strlen(arg->prefix));
}

static void	print_num(t_arg *arg, char number[LEN], int count)
{
	int	delta;

	delta = 0;
	if (arg->sign)
		delta += 1;
	if (arg->prefix)
		delta += ft_strlen(arg->prefix);
	print_space(arg, delta);
	print_sign_and_prefix(arg);
	print_zero(arg, delta, count);
	arg->res += write(1, number + LEN - count, count);
	arg->flags = arg->flags | FLAG_PRNT;
	print_space(arg, delta);
	arg->flags = arg->flags & !FLAG_PRNT;
}

void	num_printer(t_arg *arg)
{
	t_ull		num;
	t_ull		num_copy;
	int			count;
	char		number[LEN];
	static char	digits[] = "0123456789abcdef0123456789ABCDEF";

	num = get_num_type(arg);
	num_copy = num;
	count = 0;
	while (1)
	{
		number[LEN - 1 - count] = digits[(num % arg->base) + 16 * arg->is_up];
		num /= arg->base;
		(count)++;
		if (!num)
			break ;
	}
	if (arg->prec == 0 && num_copy == 0)
		count = 0;
	if (arg->prec > count)
		arg->width -= arg->prec;
	else
		arg->width -= count;
	print_num(arg, number, count);
}
