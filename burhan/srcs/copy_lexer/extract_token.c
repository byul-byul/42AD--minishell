/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_to_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/30 14:06:24 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static char	*append_char(char *str, char c)
{
	char	tmp[2];
	char	*res;

	tmp[0] = c;
	tmp[1] = '\0';
	res = ft_strjoin(str, tmp);
	free(str);
	return (res);
}

static int	extract_quoted(char **input, char quote, char **value, t_quote_type *quoted)
{
	if (*quoted == NONE)
		*quoted = (quote == '\'') ? SINGLE : DOUBLE;
	(*input)++;  // skip opening quote
	while (**input)
	{
		if (**input == quote)
		{
			(*input)++;  // skip closing quote
			return (0);
		}
		*value = append_char(*value, **input);
		(*input)++;
	}
	// Reached end of input without closing quote
	return (1);
}

static char	*extract_word_token(char **input, t_quote_type *quoted)
{
	char	*value;

	value = ft_strdup("");
	if (!value)
		return (NULL);
	while (**input && !ft_iswhitespace(**input) && !is_metachar(**input))
	{
		if (**input == '\'' || **input == '"')
		{
			if (extract_quoted(input, **input, &value, quoted))
				return (free(value), NULL);
		}
		else
		{
			value = append_char(value, **input);
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
	if (!input || !(*input))
		return (NULL);
	if (((**input == '|' || **input == '&' || **input == '<' || **input == '>'))
		&& *(*input + 1) == **input)
	{
		(*input)++;
		len = 2;
	}
	(*input)++;
	return (ft_strndup(*input - len, len));
}

void	extract_token(t_token *token, char **input)
{
	char			*value;
	t_quote_type	quoted;

	quoted = NONE;
	value = NULL;
	while (ft_iswhitespace(**input))
		(*input)++;
	if (is_metachar(**input))
		value = extract_meta_token(input);
	else
		value = extract_word_token(input, &quoted);
	token->quoted = quoted;
	token->value = value;
}
