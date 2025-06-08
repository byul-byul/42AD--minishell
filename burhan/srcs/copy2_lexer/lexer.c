/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/31 17:14:48 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

t_token	*lexer(char *input, int exit_status)
{
	t_token	*new_token;
	t_token	*last_token;
	t_token	*token_list;

	if (!input)
		return (NULL);
	new_token = fetch_token(&input, NULL, exit_status);
	if (!new_token)
		return (NULL);
	token_list = new_token;
	last_token = new_token;
	while (*input)
	{
		new_token = fetch_token(&input, last_token, exit_status);
		if (!new_token)
			return (clean_token_list(token_list), NULL);
		last_token->next = new_token;
		last_token = new_token;
	}
	return (token_list);
}
