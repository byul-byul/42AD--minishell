/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_to_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 08:51:06 by bhajili           #+#    #+#             */
/*   Updated: 2024/12/17 10:35:23 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*atoi_handler(char *str, int *sign);
static int	get_base_len(t_cchr *base);

char	*ft_convert_base(char *nbr, t_cchr *base_from, t_cchr *base_to)
{
	if (get_base_len(base_from) > 1 && get_base_len(base_to) > 1)
		return (ft_itoa_base(ft_atoi_base(nbr, base_from), base_to));
	return (NULL);
}

int	ft_atoi_base(t_cchr *nptr, t_cchr *base)
{
	t_ull	num;
	int		mltpl;
	int		sign;
	int		base_len;
	char	*str;

	num = 0;
	mltpl = 0;
	sign = 1;
	base_len = get_base_len(base);
	str = atoi_handler((char *)nptr, &sign);
	if (base_len < 2 || !str)
		return (0);
	while (*str)
	{
		mltpl = ft_charpos(*str++, base);
		if (mltpl == -1)
			break ;
		num = num * base_len + mltpl;
	}
	return ((int)(num * sign));
}

char	*ft_itoa_base(int nbr, t_cchr *base)
{
	int		base_len;
	int		num_len;
	char	*res;
	long	num;

	num = nbr;
	if (num < 0)
		num = -num;
	base_len = get_base_len(base);
	if (base_len < 2)
		return (NULL);
	num_len = ft_numlen(nbr, base_len);
	res = (char *)malloc(sizeof(char) * (num_len + 1));
	if (res)
	{
		res[num_len] = '\0';
		while (--num_len >= 0)
		{
			res[num_len] = base[num % base_len];
			num /= base_len;
		}
		if (nbr < 0)
			res[0] = '-';
	}
	return (res);
}

static char	*atoi_handler(char *str, int *sign)
{
	if (!str)
		return (NULL);
	str = ft_skipspace(str);
	if (*str == '-')
		*sign = -1;
	if (*str == '+' || *str == '-')
		str++;
	str = ft_skipchar('0', str);
	return (str);
}

static int	get_base_len(t_cchr *base)
{
	int		base_len;
	char	*tmp;

	if (!base)
		return (-1);
	base_len = 0;
	tmp = (char *)base;
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
