/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 14:08:18 by bhajili           #+#    #+#             */
/*   Updated: 2024/09/24 23:50:54 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(t_cchr *s, int c)
{
	if (s)
		while (*s != (char)c)
			if (!*s++)
				return (NULL);
	return ((char *)s);
}

char	*ft_strrchr(t_cchr *s, int c)
{
	t_cchr	*tmp;

	tmp = s;
	if (s)
	{
		while (*s)
			s++;
		while (*s != (char)c)
			if (s-- == tmp)
				return (NULL);
	}
	return ((char *)s);
}

char	*ft_strstr(t_cchr *s1, t_cchr *s2)
{
	return (ft_strnstr(s1, s2, ft_strlen(s1)));
}

char	*ft_strnstr(t_cchr *s1, t_cchr *s2, size_t len)
{
	size_t	s2_len;

	if (!(*s2))
		return ((char *)s1);
	s2_len = ft_strlen(s2);
	if (ft_strlen(s1) < s2_len)
		return (NULL);
	while (len-- >= s2_len)
		if (!ft_strncmp(s1++, s2, s2_len))
			return ((char *)(s1 - 1));
	return (NULL);
}
