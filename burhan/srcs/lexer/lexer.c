/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/12 22:14:45 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static int	ft_iswhitespacestr(char *str)
{
	if (!str)
		return (0);
	while (*str)
		if (!ft_iswhitespace(*str++))
			return (0);
	return (1);
}

t_token	*lexer(char *input, int exit_status)
{
	t_token	*new_token;
	t_token	*last_token;
	t_token	*token_list;

	if (!input || ft_iswhitespacestr(input))
		return (NULL);
	new_token = fetch_token(&input, exit_status);
	if (!new_token)
		return (NULL);
	token_list = new_token;
	last_token = new_token;
	while (*input)
	{
		new_token = fetch_token(&input, exit_status);
		if (!new_token)
			return (clean_token_list(token_list), NULL);
		if (is_heredoc_expand(last_token, new_token->quoted))
			new_token->heredoc_expand = TRUE;
		last_token->next = new_token;
		last_token = new_token;
	}
	return (token_list);
}
