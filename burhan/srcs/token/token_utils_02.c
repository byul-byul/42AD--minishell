/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/30 13:10:56 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_wrapper.h"

// int	remove_quotes(t_token *token)
// {
// 	char	*stripped;
// 	char	*new_map;
// 	size_t	i;

// 	if (!token || !token->value || !token->quote_map)
// 		return ;
// 	stripped = ft_strdup("");
// 	if (!stripped)
// 		return (0);
// 	new_map = ft_strdup("");
// 	if (!new_map)
// 		return (free(stripped), 0);
// 	i = -1;
// 	while (token->value[++i])
// 	{
// 		if (token->quote_map[i] != '1' && token->quote_map[i] != '2')
// 			if (!ft_safeappendchar(&stripped, token->value[i]) ||
// 				!ft_safeappendchar(&new_map, token->quote_map[i]))
// 				return (free(stripped), free(new_map), 0);
// 	}
// 	free(token->value);
// 	free(token->quote_map);
// 	token->value = stripped;
// 	token->quote_map = new_map;
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
			continue ;
		}
		if (!ft_safeappendchar(value, **input)
			|| !ft_safeappendchar(quote_map, '0'))
			return (free(*value), free(*quote_map), 0);
		(*input)++;
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
