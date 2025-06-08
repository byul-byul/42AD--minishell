/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 02:54:57 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/31 17:36:19 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

char	*safe_append_char(char *str, char c)
{
	char	append[2];
	char	*res;

	if (!str)
		return (NULL);
	append[0] = c;
	append[1] = '\0';
	res = ft_strjoin(str, append);
	free(str);
	return (res);
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

int	is_heredoc_expand(t_token *prev, t_quote_type quote_type)
{
	return (prev && prev->type == HEREDOC && quote_type != SINGLE);
}
