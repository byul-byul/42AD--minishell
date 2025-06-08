/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/31 21:35:12 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static int	extract_quoted(char **input, char quote, char **value,
						t_quote_type *quoted)
{
	if (*quoted == NONE)
	{
		*quoted = DOUBLE;
		if (quote == '\'')
			*quoted = SINGLE;
	}
	(*input)++;
	while (**input)
	{
		if (**input == quote)
		{
			(*input)++;
			return (0);
		}
		*value = safe_append_char(*value, **input);
		if (!*value)
			return (1);
		(*input)++;
	}
	return (1);
}

static char	*extract_word_token(char **input, t_quote_type *quoted)
{
	char	*value;

	if (!input || !*input)
		return (NULL);
	value = ft_strdup("");
	if (!value)
		return (NULL);
	while (**input && !ft_iswhitespace(**input) && !is_metachar(**input))
	{
		if (is_quoting(**input))
		{
			if (extract_quoted(input, **input, &value, quoted))
				return (free(value), NULL);
		}
		else
		{
			value = safe_append_char(value, **input);
			if (!value)
				return (NULL);
			(*input)++;
		}
	}
	return (value);
}

static char	*extract_meta_token(char **input)
{
	int	len;

	len = 1;
	if (!input || !*input)
		return (NULL);
	if (is_operator_char(**input) && *(*input + 1) == **input)
	{
		(*input)++;
		len = 2;
	}
	(*input)++;
	return (ft_strndup(*input - len, len));
}

void	extract_token_value(char **input, t_token *token)
{
	char			*value;
	t_quote_type	quoted;

	quoted = NONE;
	if (!input || !*input)
		return ;
	while (ft_iswhitespace(**input))
		(*input)++;
	if (is_metachar(**input))
		value = extract_meta_token(input);
	else
		value = extract_word_token(input, &quoted);
	token->quoted = quoted;
	token->value = value;
}
