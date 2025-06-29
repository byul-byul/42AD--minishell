/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:23:02 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 09:12:12 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_arrlen(t_cchr **arr, size_t size)
{
	size_t	i;
	size_t	arrlen;

	i = -1;
	arrlen = 0;
	if (arr)
		while (++i < size)
			arrlen += ft_strlen(arr[i]);
	return (arrlen);
}

void	ft_freearr(char **arr, ssize_t size)
{
	ssize_t	i;

	i = -1;
	if (!arr)
		return ;
	while (++i < size)
		if (arr[i])
			free(arr[i]);
	free(arr);
}

size_t	ft_arrsize(char **arr)
{
	size_t	size;

	size = 0;
	if (!arr)
		return (size);
	while (arr[size])
		size++;
	return (size);
}

char	**ft_arrdup(char **src, size_t size)
{
	char	**dup;
	size_t	i;

	i = 0;
	if (!src || ft_arrsize(src) != size)
		return (NULL);
	dup = malloc(sizeof(char *) * (size + 1));
	if (!dup)
		return (NULL);
	while (i < size)
	{
		dup[i] = ft_strdup(src[i]);
		if (!dup[i])
			return (ft_freearr(dup, i), NULL);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
