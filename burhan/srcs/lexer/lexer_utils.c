/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 02:54:57 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/14 02:46:50 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

int	is_heredoc_expand(t_token *prev, t_quote_type quote_type)
{
	return (prev && prev->type == HEREDOC && quote_type != SINGLE);
}

// int	is_word_token_type(t_token_type type)
// {
// 	return (WORD == type);
// }

void	clean_token_list(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list->next;
		free(token_list->value);
		free(token_list);
		token_list = tmp;
	}
}

int	is_operator_char(int c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	is_subshell_paren(int c)
{
	return (c == '(' || c == ')');
}

int	is_metachar(int c)
{
	return (is_subshell_paren(c) || is_operator_char(c));
}

