/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/15 14:01:26 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_wrapper.h"

static int	extract_quoted(char **input, char quote, char **value,
						t_quote_type *quoted)
{
	(*input)++;
	if (*quoted == NONE && quote == '\'')
		*quoted = SINGLE;
	if (*quoted == NONE && quote == '"')
		*quoted = DOUBLE;
	while (**input)
	{
		if (**input == quote)
			return ((*input)++, 1);
		if (quote == '"' && **input == '\\')
		{
			(*input)++;
			if (!ft_safeappendchar(value, **input))
				return (0);
		}
		else if (!ft_safeappendchar(value, **input))
			return (0);
		(*input)++;
	}
	return (0);
}

static int	append_token_content(char **input, char **value,
	t_quote_type *local)
{
	char	prev;

	prev = '\0';
	while (**input && !ft_isspace(**input) && !is_meta_token(**input))
	{
		if (ft_isquote(**input) && prev != '\\')
		{
			if (!extract_quoted(input, **input, value, local))
				return (0);
		}
		else
		{
			if (!ft_safeappendchar(value, **input))
				return (0);
			prev = **input;
			(*input)++;
		}
	}
	return (1);
}

static char	*extract_word_token(char **input, t_quote_type *quoted)
{
	char			*value;
	t_quote_type	local;

	if (!input || !*input)
		return (NULL);
	value = ft_strdup("");
	if (!value)
		return (NULL);
	local = NONE;
	if (ft_isquote(**input))
	{
		if (!extract_quoted(input, **input, &value, &local))
			return (free(value), NULL);
		if (!**input || ft_isspace(**input) || is_meta_token(**input))
			*quoted = local;
	}
	if (!append_token_content(input, &value, &local))
		return (free(value), NULL);
	return (value);
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
	char			*value;
	t_quote_type	quoted;

	quoted = NONE;
	if (!input || !*input)
		return ;
	if (is_meta_token(**input))
		value = extract_meta_token(input);
	else
		value = extract_word_token(input, &quoted);
	token->quoted = quoted;
	token->value = value;
}
