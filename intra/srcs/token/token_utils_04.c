/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_04.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 14:56:49 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_wrapper.h"

// int	remove_quotes(t_token *token)
// {
// 	char	*stripped;
// 	char	*new_map;
// 	size_t	i;

// 	if (!token || !token->value || !token->quote_map)
// 		return ;
// 	stripped = ft_strdup("");
// 	if (!stripped)
// 		return (0);
// 	new_map = ft_strdup("");
// 	if (!new_map)
// 		return (free(stripped), 0);
// 	i = -1;
// 	while (token->value[++i])
// 	{
// 		if (token->quote_map[i] != '1' && token->quote_map[i] != '2')
// 			if (!ft_safeappendchar(&stripped, token->value[i]) ||
// 				!ft_safeappendchar(&new_map, token->quote_map[i]))
// 				return (free(stripped), free(new_map), 0);
// 	}
// 	free(token->value);
// 	free(token->quote_map);
// 	token->value = stripped;
// 	token->quote_map = new_map;
// 	return (1);
// }

void	tokenlist_push_back(t_token **head, t_token *new_token)
{
	t_token	*curr;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	curr = *head;
	while (curr->next)
		curr = curr->next;
	curr->next = new_token;
}
