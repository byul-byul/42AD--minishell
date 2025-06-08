/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_07.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 22:28:17 by bhajili           #+#    #+#             */
/*   Updated: 2024/09/24 23:51:28 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charpos(char c, t_cchr *str)
{
	char	*pos;

	pos = ft_strchr(str, c);
	if (pos)
		return (pos - str);
	return (-1);
}

size_t	ft_substrlen(char *str, t_cchr *charset)
{
	size_t	len;

	len = 0;
	while (str[len] && !ft_isinstr(str[len], charset))
		len++;
	return (len);
}

int	ft_substrcount(char *str, t_cchr *charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		str = ft_skipcharset(str, charset);
		if (!*str)
			break ;
		str = ft_keepcharset(str, charset);
		count++;
	}
	return (count);
}
