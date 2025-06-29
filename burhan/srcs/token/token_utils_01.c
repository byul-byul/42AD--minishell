/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 10:41:13 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_wrapper.h"

int	is_heredoc_expand(t_token *prev, const char *quote_map)
{
	return (prev && prev->type == HEREDOC && quote_map && quote_map[0] != '1');
}

int	is_token_operator(int c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	is_meta_token(int c)
{
	return (ft_isparentheses(c) || is_token_operator(c));
}

int	is_redirect_token(t_token_type type)
{
	return (type == REDIR_IN || type == REDIR_OUT
		|| type == HEREDOC || type == APPEND);
}
