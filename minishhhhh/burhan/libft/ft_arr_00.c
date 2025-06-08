/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arr_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 13:23:02 by bhajili           #+#    #+#             */
/*   Updated: 2025/02/24 14:35:14 by bhajili          ###   ########.fr       */
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

void	ft_freearr(char **arr, size_t size)
{
	size_t	i;

	i = -1;
	if (!arr)
		return ;
	while (++i < size)
		if (arr[i])
			free(arr[i]);
	free(arr);
}
