/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 02:54:57 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/12 16:15:58 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

int	is_heredoc_expand(t_token *prev, t_quote_type quote_type)
{
	return (prev && prev->type == HEREDOC && quote_type != SINGLE);
}

int	is_word_token_type(t_token_type type)
{
	return (WORD == type);
}

int	safe_append_char(char **str, char c)
{
	char	append[2];

	if (!*str)
		return (0);
	append[0] = c;
	append[1] = '\0';
	return (safe_append_str(str, append));
}

int	safe_append_str(char **str, char *append)
{
	char	*res;

	if (!*str)
		return (0);
	res = ft_strjoin(*str, append);
	if (!res)
		return (0);
	free(*str);
	*str = res;
	return (1);
}

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
