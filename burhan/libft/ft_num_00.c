/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_num_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 09:08:23 by bhajili           #+#    #+#             */
/*   Updated: 2024/12/17 10:36:47 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sqrt(int nb, int i)
{
	if ((i * i) > nb)
		return (0);
	else if ((i * i) == nb)
		return (i);
	return (get_sqrt(nb, i + 1));
}

int	ft_sqrt(int nb)
{
	if (nb < 0 || nb > MAX_SQRT_INT)
		return (0);
	return (get_sqrt(nb, 1));
}

int	ft_factorial(int nb)
{
	if (nb < 0)
		return (0);
	if (nb == 0 || nb == 1)
		return (1);
	else
		return (nb * ft_factorial(nb - 1));
}

int	ft_power(int nb, int power)
{
	if (power == 0)
		return (1);
	if (power < 0)
		return (0);
	if (power == 1)
		return (nb);
	else
		return (nb * ft_power(nb, power - 1));
}

int	ft_numlen(t_ll num, int base_len)
{
	int		numlen;

	numlen = 1;
	if (num < 0)
		numlen++;
	while (num / base_len)
	{
		num /= base_len;
		numlen++;
	}
	return (numlen);
}
