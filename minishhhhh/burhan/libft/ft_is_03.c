/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 15:44:08 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/14 22:44:49 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprime(int nb)
{
	int	i;

	i = 2;
	if (nb < 2)
		return (0);
	while (i <= (nb / i))
		if ((nb++ % i) == 0)
			return (0);
	return (1);
}

int	ft_issquare(int nb)
{
	if (nb == 0 || ft_sqrt(nb))
		return (1);
	return (0);
}

int	ft_iswhitespace(int c)
{
	return (c == 32);
}
