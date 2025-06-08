/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_05.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 17:06:20 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/05 15:56:39 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(t_cchr *s1, t_cchr *s2)
{
	return (ft_strljoin(s1, s2, ft_strlen(s1), ft_strlen(s2)));
}

char	*ft_strljoin(t_cchr *s1, t_cchr *s2, size_t len1, size_t len2)
{
	t_cchr	*arr[3];
	size_t	lens[2];

	arr[0] = s1;
	arr[1] = s2;
	arr[2] = NULL;
	lens[0] = len1;
	lens[1] = len2;
	return (ft_strljoin_charset(2, lens, arr, ""));
}

char	*ft_strjoin_charset(int size, t_cchr **strs, t_cchr *sep)
{
	size_t	*lens;
	char	*res;
	int		i;

	i = -1;
	lens = (size_t *)malloc(sizeof(size_t) * size);
	if (!lens)
		return (NULL);
	while (++i < size)
		lens[i] = ft_strlen(strs[i]);
	res = ft_strljoin_charset(size, lens, strs, sep);
	free(lens);
	return (res);
}

char	*ft_strljoin_charset(int s, size_t *lens, t_cchr **strs, t_cchr *sep)
{
	long	tot_len;
	char	*res;
	int		i;

	i = -1;
	tot_len = ft_strlen(sep) * (s - 1);
	if (!strs || !(*strs) || s <= 0)
		return (NULL);
	while (++i < s)
		tot_len += lens[i];
	res = (char *)malloc(sizeof(char) * (tot_len + 1));
	if (res)
	{
		i = -1;
		res[0] = '\0';
		while (++i < s)
		{
			ft_strncat(res, strs[i], lens[i]);
			if (i < s - 1)
				ft_strcat(res, sep);
		}
		res[tot_len] = '\0';
	}
	return (res);
}
