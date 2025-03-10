/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 14:27:38 by bhajili           #+#    #+#             */
/*   Updated: 2024/12/16 14:15:47 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_base_len(t_cchr *base)
{
	int		base_len;
	t_cchr	*tmp;

	if (!base)
		return (-1);
	base_len = 0;
	tmp = base;
	while (*tmp)
	{
		if (*tmp == '+' || *tmp == '-')
			return (-1);
		if (ft_isduplicate(*tmp, tmp, base))
			return (-1);
		if (ft_isspace(*tmp))
			return (-1);
		tmp++;
		base_len++;
	}
	return (base_len);
}

static void	ft_putnbr_r(t_ll num, int base_len, t_cchr *base, int fd)
{
	if (num != 0)
	{
		ft_putnbr_r(num / base_len, base_len, base, fd);
		ft_putchar_fd(*(base + num % base_len), fd);
	}
}

void	ft_putnbr_base(t_ll nbr, t_cchr *base)
{
	ft_putnbr_base_fd(nbr, base, 1);
}

void	ft_putnbr_base_fd(t_ll nbr, t_cchr *base, int fd)
{
	int		base_len;
	int		num_len;
	t_ll	num;

	base_len = get_base_len(base);
	num_len = ft_numlen(nbr, base_len);
	num = nbr;
	if (base_len < 2)
		return ;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		if (num == -MAX_LL - 1)
		{
			ft_putchar_fd(num / -(num_len - 2) + '0', fd);
			num = num % -(num_len - 2);
		}
		else
			num = -num;
	}
	if (num == 0)
		ft_putchar_fd(*base, fd);
	ft_putnbr_r(num, base_len, base, fd);
}
