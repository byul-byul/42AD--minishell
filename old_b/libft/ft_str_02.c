/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:12:36 by bhajili           #+#    #+#             */
/*   Updated: 2024/12/28 19:09:35 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(t_cchr *s)
{
	return (ft_strndup(s, ft_strlen(s)));
}

char	*ft_strndup(t_cchr *s, size_t n)
{
	return (ft_substr(s, 0, n));
}

char	*ft_substr(t_cchr *str, t_unint start, size_t len)
{
	char	*res;
	size_t	sublen;

	if (!str)
		return (NULL);
	sublen = ft_strlen(str);
	if (sublen <= start)
		sublen = 0;
	else
		sublen -= start;
	if (sublen > len)
		sublen = len;
	res = (char *)malloc(sizeof(char) * (sublen + 1));
	if (res)
	{
		ft_strncpy(res, str + start, sublen);
		res[sublen] = '\0';
	}
	return (res);
}

char	*ft_strtrim(t_cchr *str, t_cchr *set)
{
	size_t	str_len;

	if (!str)
		return (NULL);
	if (!set)
		return (ft_strdup(str));
	while (*str && ft_strchr(set, *str))
		str++;
	str_len = ft_strlen(str);
	while (str_len && ft_strchr(set, str[str_len]))
		str_len--;
	return (ft_strndup(str, str_len + 1));
}
