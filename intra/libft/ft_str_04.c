/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_04.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:57:57 by bhajili           #+#    #+#             */
/*   Updated: 2024/12/16 16:23:00 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**split_handler(int size, char *str, t_cchr *charset)
{
	size_t	split_len;
	char	**splits;
	int		i;

	i = -1;
	splits = (char **)(malloc(sizeof(char *) * (size + 1)));
	if (splits)
	{
		while (++i < size)
		{
			str = ft_skipcharset(str, charset);
			split_len = ft_substrlen(str, charset);
			splits[i] = ft_strndup(str, split_len);
			if (NULL == splits[i])
			{
				ft_freearr(splits, size);
				return (NULL);
			}
			str += split_len;
		}
		splits[size] = NULL;
	}
	return (splits);
}

char	**ft_split(t_cchr *arr, char c)
{
	char	charset[2];

	charset[0] = c;
	charset[1] = '\0';
	return (ft_split_charset(arr, (t_cchr *)charset));
}

char	**ft_split_charset(t_cchr *arr, t_cchr *charset)
{
	char	*str;

	if (!arr)
		return (NULL);
	str = (char *)arr;
	return (split_handler(ft_substrcount(str, charset), str, charset));
}

char	*ft_strmapi(t_cchr *str, char (*f)(t_unint, char))
{
	char	*res;
	int		i;

	if (!str || !f)
		return (NULL);
	res = ft_strdup(str);
	if (res)
	{
		i = -1;
		while (res[++i])
			res[i] = f(i, res[i]);
	}
	return (res);
}

void	ft_striteri(char *s, void (*f)(t_unint, char *))
{
	t_unint	i;

	if (!s || !f)
		return ;
	i = -1;
	while (s[++i])
		f(i, s + i);
}
