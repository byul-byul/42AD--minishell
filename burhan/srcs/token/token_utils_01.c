/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/15 14:01:10 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_wrapper.h"

int	is_heredoc_expand(t_token *prev, t_quote_type quote_type)
{
	return (prev && prev->type == HEREDOC && quote_type != SINGLE);
}

int	is_token_operator(int c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	is_meta_token(int c)
{
	return (ft_isparentheses(c) || is_token_operator(c));
}
