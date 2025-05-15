/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_to_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/15 13:30:50 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static void	handle_metachar(char **input)
{
	if (((**input == '|' || **input == '&' || **input == '<' || **input == '>'))
		&& (*(*input + 1) == **input))
		(*input)++;
	(*input)++;
}

static int	handle_word_token(t_token *token, char **input)
{
	char	quote;

	while (**input && !ft_iswhitespace(**input) && !is_metachar(**input))
	{
		if (**input == '\'' || **input == '"')
		{
			quote = **input;
			(*input)++;
			while (**input && **input != quote)
				(*input)++;
			if (**input != quote)
				return (1);
			token->quoted = TRUE;
			(*input)++;
		}
		else
			(*input)++;
	}
	return (0);
}

void	extract_to_token(t_token *token, char **input)
{
	char	*start;

	start = *input;
	if (is_metachar(**input))
		handle_metachar(input);
	else
	{
		if (handle_word_token(token, input))
		{
			token->value = NULL;
			return ;
		}
	}
	token->value = ft_strndup(start, *input - start);
}
