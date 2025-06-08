/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:31:58 by bhajili           #+#    #+#             */
/*   Updated: 2024/09/24 23:56:39 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	return (ft_memccpy(dest, src, -1, n));
}

void	*ft_memset(void *s, int c, size_t n)
{
	t_unchr	*ptr;

	ptr = s;
	while (n > 0 && n--)
		*ptr++ = (t_unchr)c;
	return (s);
}

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const t_unchr	*src_ptr;
	t_unchr			*dst_ptr;

	if (dest == src || n <= 0)
		return (dest);
	src_ptr = src;
	dst_ptr = dest;
	if (c == -1)
	{
		while (n--)
			*dst_ptr++ = *src_ptr++;
		return (dest);
	}
	while (n--)
	{
		*dst_ptr++ = *src_ptr++;
		if (*(src_ptr - 1) == (t_unchr)c)
			return ((void *)dst_ptr);
	}
	return (NULL);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const t_unchr	*src_ptr;
	t_unchr			*dst_ptr;

	if (dest == src)
		return (dest);
	src_ptr = src;
	dst_ptr = dest;
	if (dst_ptr < src_ptr)
		while (n > 0 && n--)
			*dst_ptr++ = *src_ptr++;
	else
	{
		dst_ptr += n - 1;
		src_ptr += n - 1;
		while (n > 0 && n--)
			*dst_ptr-- = *src_ptr--;
	}
	return (dest);
}
