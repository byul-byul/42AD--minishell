/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:20:23 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 09:23:26 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_wrapper.h"

// int	quote_remover(t_token *token)
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

void	print_expander_result(t_token *token_list)
{
	ft_printf(C_BLUE "expander() returned:\n" C_RESET);
	print_token_list(token_list);
}

t_token	*expander(t_token *token_list, t_env *env)
{
	char			*tmp;
	char			*expanded;
	t_token			*head;

	head = token_list;
	while (token_list)
	{
		if (token_list->type == WORD && token_list->value
			&& token_list->quote_map)
		{
			tmp = token_list->value;
			expanded = expand_token_value(token_list->value,
					token_list->quote_map, env);
			if (!expanded)
				return (free(tmp), NULL);
			if (ft_strcmp(tmp, expanded))
				token_list->expanded = 1;
			token_list->value = expanded;
			free(tmp);
			token_list->type = get_token_type(token_list->value,
					token_list->quote_map);
		}
		token_list = token_list->next;
	}
	return (head);
}
