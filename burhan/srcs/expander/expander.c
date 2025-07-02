/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:20:23 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 15:19:56 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_wrapper.h"

void	print_expander_result(t_token *token_list)
{
	ft_printf(C_BLUE "expander() returned:\n" C_RESET);
	print_token_list(token_list);
}

static int	is_valid_for_expansion(t_token *token)
{
	return (token && token->type == WORD && token->value && token->quote_map);
}

// t_token	*expander(t_token *token_list, t_env *env)
// {
// 	t_token	*head;
// 	t_token	*next;

// 	head = token_list;
// 	while (token_list)
// 	{
// 		if (is_valid_for_expansion(token_list))
// 			if (!handle_dollar_expansion(token_list, env))
// 				return (NULL);
// 		token_list = token_list->next;
// 	}
// 	token_list = head;
// 	while (token_list)
// 	{
// 		next = token_list->next;
// 		if (is_valid_for_expansion(token_list))
// 			if (!handle_wildcard_expansion(token_list))
// 				return (NULL);
// 		token_list = next;
// 	}
// 	return (head);
// }

t_token	*expander(t_token *token_list, t_env *env)
{
	t_token	*head;
	t_token	*next;

	head = token_list;
	while (token_list)
	{
		if (is_valid_for_expansion(token_list))
			if (!handle_dollar_expansion(token_list, env))
				return (NULL);
		token_list = token_list->next;
	}
	token_list = head;
	while (token_list)
	{
		next = token_list->next;
		if (is_valid_for_expansion(token_list))
			if (!handle_wildcard_expansion(&head, token_list))
				return (NULL);
		token_list = next;
	}
	return (head);
}
