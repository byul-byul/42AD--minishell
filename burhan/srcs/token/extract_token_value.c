/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/15 22:21:24 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_wrapper.h"

// static int	ft_safeappendchar_map(char **map, char c)
// {
// 	char	*new;
// 	int		len;

// 	if (!map || !*map)
// 		return (0);
// 	len = ft_strlen(*map);         // ← ТОЛЬКО для корректных строк
// 	new = malloc(len + 2);         // +1 символ + '\0'
// 	if (!new)
// 		return (0);
// 	ft_memcpy(new, *map, len);
// 	new[len] = c;
// 	new[len + 1] = '\0';
// 	free(*map);
// 	*map = new;
// 	return (1);
// }

static int	extract_quoted(char **input, char quote,
				char **value, char **quote_map)
{
	char	qchar;

	if (!input || !*input || !value || !*value || !quote_map || !*quote_map)
		return (0);
	qchar = '1';
	if (quote == '\"')
		qchar = '2';
	(*input)++;
	while (**input)
	{
		if (**input == quote)
			return ((*input)++, 1);
		if (quote == '"' && **input == '\\' && *(*input + 1))
		{
			(*input)++;
			if (!ft_safeappendchar(value, **input)
				|| !ft_safeappendchar(quote_map, qchar))
				return (0);
		}
		else if (!ft_safeappendchar(value, **input)
			|| !ft_safeappendchar(quote_map, qchar))
			return (0);
		(*input)++;
	}
	return (0);
}

static int	extract_word_token(char **input, char **value, char **quote_map)
{
	if (!input || !*input)
		return (0);
	*value = ft_strdup("");
	if (!*value)
		return (0);
	*quote_map = ft_strdup("");
	if (!*quote_map)
		return (free(*value), 0);
	while (**input && !ft_isspace(**input) && !is_meta_token(**input))
	{
		if (ft_isquote(**input))
		{
			if (!extract_quoted(input, **input, value, quote_map))
				return (free(*value), free(*quote_map), 0);
		}
		else
		{
			if (!ft_safeappendchar(value, **input)
				|| !ft_safeappendchar(quote_map, '0'))
				return (free(*value), free(*quote_map), 0);
			(*input)++;
		}
	}
	return (1);
}

static char	*extract_meta_token(char **input)
{
	char	*start;
	int		len;

	len = 1;
	start = *input;
	if (!input || !*input)
		return (NULL);
	if (is_token_operator(**input) && *(*input + 1) == **input)
		len = 2;
	*input += len;
	return (ft_strndup(start, len));
}

void	extract_token_value(char **input, t_token *token)
{
	char	*value;
	char	*quote_map;

	value = NULL;
	quote_map = NULL;
	if (!input || !*input)
		return ;
	if (is_meta_token(**input))
		value = extract_meta_token(input);
	else if (!extract_word_token(input, &value, &quote_map))
		return ;
	token->value = value;
	token->quote_map = quote_map;
}
