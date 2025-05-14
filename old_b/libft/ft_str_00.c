/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:33:20 by bhajili           #+#    #+#             */
/*   Updated: 2024/09/25 00:08:09 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(t_cchr *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

int	ft_strcmp(t_cchr *s1, t_cchr *s2)
{
	size_t	len;
	size_t	size;

	len = ft_strlen(s1);
	size = ft_strlen(s2);
	if (len > size)
		size = len;
	return (ft_strncmp(s1, s2, size));
}

int	ft_strncmp(t_cchr *s1, t_cchr *s2, size_t n)
{
	size_t	len;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (-(*s2));
	if (!s2)
		return (*s1);
	len = ft_strlen(s1) + 1;
	if (len > n)
		len = n;
	return (ft_memcmp((const void *)s1, (const void *)s2, len));
}

size_t	ft_strlcat(char *dest, t_cchr *src, size_t size)
{
	size_t	dest_len;

	dest_len = ft_strlen(dest);
	if (dest_len >= size)
		return (ft_strlen(src) + size);
	ft_strlcpy(dest + dest_len, src, size - dest_len);
	return (dest_len + ft_strlen(src));
}

size_t	ft_strlcpy(char *dst, t_cchr *src, size_t size)
{
	size_t	i;

	i = -1;
	if (!dst || !src)
		return (0);
	if (size == 0)
		return (ft_strlen(src));
	while (src[++i] && i < size - 1)
		dst[i] = src[i];
	if (size != 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}
