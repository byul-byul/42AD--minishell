/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 08:57:19 by bhajili           #+#    #+#             */
/*   Updated: 2024/12/16 20:01:31 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const t_unchr	*s_ptr;

	s_ptr = s;
	while (n > 0 && n--)
		if (*s_ptr++ == (t_unchr)c)
			return ((void *)(s_ptr - 1));
	return (NULL);
}

void	*ft_memrchr(const void *s, int c, size_t n)
{
	const t_unchr	*s_ptr;

	s_ptr = s;
	while (*s_ptr)
		s_ptr++;
	while (n > 0 && n--)
		if (*s_ptr-- == (t_unchr)c)
			return ((void *)(s_ptr + 1));
	return (NULL);
}

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const t_unchr	*s1_ptr;
	const t_unchr	*s2_ptr;

	s1_ptr = s1;
	s2_ptr = s2;
	while (n > 0 && n--)
		if (*s1_ptr++ != *s2_ptr++)
			return (*(s1_ptr - 1) - *(s2_ptr - 1));
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (size && nmemb > SIZE_MAX / size)
		return (NULL);
	res = (void *)malloc(nmemb * size);
	if (res)
		ft_bzero(res, nmemb * size);
	return (res);
}
