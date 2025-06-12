/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_token_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/12 16:39:16 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

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
			if (!safe_append_char(value, **input))
				return (0);
		}
		else if (!safe_append_char(value, **input))
			return (0);
		(*input)++;
	}
	return (0);
}

static char	*extract_word_token(char **input, t_quote_type *quoted)
{
	char	*value;
	char	prev_char;

	if (!input || !*input)
		return (NULL);
	value = ft_strdup("");
	if (!value)
		return (NULL);
	prev_char = '\0';
	while (**input && !ft_iswhitespace(**input) && !is_metachar(**input))
	{
		if (is_quoting(**input) && prev_char != '\\')
		{
			if (!extract_quoted(input, **input, &value, quoted))
				return (free(value), NULL);
			prev_char = '\0';
		}
		else
		{
			if (!safe_append_char(&value, **input))
				return (free(value), NULL);
			prev_char = **input;
			(*input)++;
		}
	}
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
	if (is_operator_char(**input) && *(*input + 1) == **input)
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
	if (is_metachar(**input))
		value = extract_meta_token(input);
	else
		value = extract_word_token(input, &quoted);
	token->quoted = quoted;
	token->value = value;
}
