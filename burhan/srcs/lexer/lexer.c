/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 12:07:53 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static t_token	*lexing_input(char *input)
{
	t_token	*new_token;
	t_token	*last_token;
	t_token	*token_list;

	if (!input)
		return (NULL);
	new_token = fetch_token(&input);
	if (!new_token)
		return (NULL);
	token_list = new_token;
	last_token = new_token;
	while (*input)
	{
		if (*input == '#')
			break ;
		new_token = fetch_token(&input);
		if (!new_token)
			return (clean_token_list(token_list), NULL);
		if (is_heredoc_expand(last_token, new_token->quote_map))
			new_token->heredoc_expand = TRUE;
		last_token->next = new_token;
		last_token = new_token;
	}
	return (token_list);
}

t_token	*lexer(char *input)
{
	if (!input || ft_isspacestr(input))
		return (NULL);
	while (ft_isspace(*input))
		input++;
	if (*input == '#')
		return (NULL);
	return (lexing_input(input));
}
