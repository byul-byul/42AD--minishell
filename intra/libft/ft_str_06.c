/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_06.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:28:55 by bhajili           #+#    #+#             */
/*   Updated: 2024/09/24 23:51:19 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_skipspace(char *str)
{
	return (ft_skipcharset(str, SPACE_SET));
}

char	*ft_skipchar(char c, char *str)
{
	char	charset[2];

	charset[0] = c;
	charset[1] = '\0';
	return (ft_skipcharset(str, charset));
}

char	*ft_skipcharset(char *str, t_cchr *charset)
{
	if (!str)
		return (NULL);
	if (!charset)
		return (str);
	while (*str && ft_isinstr(*str, charset))
		str++;
	return (str);
}

char	*ft_keepcharset(char *str, t_cchr *charset)
{
	if (!str)
		return (NULL);
	if (!charset)
		return (str);
	while (*str && !ft_isinstr(*str, charset))
		str++;
	return (str);
}
