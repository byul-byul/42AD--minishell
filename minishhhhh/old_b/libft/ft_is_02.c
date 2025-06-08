/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 06:42:31 by bhajili           #+#    #+#             */
/*   Updated: 2024/09/24 23:46:23 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalphas(t_cchr *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_isalpha(*str++))
			return (0);
	return (1);
}

int	ft_isdigits(t_cchr *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_isdigit(*str++))
			return (0);
	return (1);
}

int	ft_isxdigits(t_cchr *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_isxdigit(*str++))
			return (0);
	return (1);
}

int	ft_isalnums(t_cchr *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_isalnum(*str++))
			return (0);
	return (1);
}

int	ft_isduplicate(int c, t_cchr *pos, t_cchr *str)
{
	if (!pos || !str)
		return (0);
	while (*str && str != pos)
		if (c == *str++)
			return (1);
	return (0);
}
