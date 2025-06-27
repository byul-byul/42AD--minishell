/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/27 03:22:39 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

void	print_lexer_result(char *input, t_token *token_list)
{
	ft_printf(C_BLUE "lexer() for input \"%s\" returned:\n" C_RESET, input);
	print_token_list(token_list);
}

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
