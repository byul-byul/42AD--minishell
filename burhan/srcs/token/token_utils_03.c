/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_03.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 03:11:29 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/27 04:24:32 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_wrapper.h"

static const char	*token_type_str(t_token_type type)
{
	static const char	*types[] = {
		"WORD", "PIPE", "REDIR_IN", "REDIR_OUT", "HEREDOC", "APPEND",
		"LOGICAL_AND", "LOGICAL_OR", "OPEN_PAREN", "CLOSE_PAREN"
	};

	if (type >= 0 && type <= CLOSE_PAREN)
		return (types[type]);
	return ("UNKNOWN");
}

static void	print_token(t_token *token)
{
	if (!token)
		return ;
	ft_printf(C_YELLOW "token:" C_WHITE
		" [value=\"%-12s\"] [type=%-12s] ",
		token->value, token_type_str(token->type));
	if (token->quote_map)
		ft_printf("[quote_map=\"%-12s\"] ", token->quote_map);
	else
		ft_printf("[quote_map=%-14s] ", "NULL");
	ft_printf("[heredoc_expand=%-2d] [expanded=%-2d]",
		token->heredoc_expand, token->expanded);
	ft_putendl(C_RESET);
}

void	print_token_list(t_token *list)
{
	while (list)
	{
		print_token(list);
		list = list->next;
	}
}
