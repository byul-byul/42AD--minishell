/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_03.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 13:41:08 by bhajili           #+#    #+#             */
/*   Updated: 2024/12/26 13:41:41 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_ull	dec_handler(t_arg *arg)
{
	t_ull		num;
	long int	n;

	n = va_arg(arg->value, int);
	if (n < 0)
	{
		arg->sign = '-';
		num = -n;
	}
	else
	{
		if (flag_check(arg, FLAG_PLUS))
			arg->sign = '+';
		else if (flag_check(arg, FLAG_SPCE))
			arg->sign = ' ';
		num = n;
	}
	arg->base = 10;
	return (num);
}

static t_ull	hex_handler(t_arg *arg)
{
	t_ull	num;

	num = va_arg(arg->value, unsigned);
	if (flag_check(arg, FLAG_SHRP) && num != 0)
	{
		if (arg->type == 'X')
			arg->prefix = "0X";
		else
			arg->prefix = "0x";
	}
	else
		arg->prefix = "";
	arg->base = 16;
	arg->is_up = arg->type == 'X';
	return (num);
}

t_ull	get_num_type(t_arg *arg)
{
	t_ull	num;

	num = 0;
	arg->is_up = 0;
	arg->sign = '\0';
	arg->prefix = NULL;
	if (arg->type == 'u')
	{
		num = va_arg(arg->value, unsigned);
		arg->base = 10;
	}
	else if (arg->type == 'p')
	{
		num = (t_ull)va_arg(arg->value, void *);
		arg->prefix = "0x";
		arg->base = 16;
	}
	else if (arg->type == 'd' || arg->type == 'i')
		num = dec_handler(arg);
	else if (arg->type == 'x' || arg->type == 'X')
		num = hex_handler(arg);
	return (num);
}
