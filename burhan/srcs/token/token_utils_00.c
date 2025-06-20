/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/16 21:04:22 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token_wrapper.h"

void	clean_token_list(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list->next;
		free(token_list->value);
		if (token_list->type == WORD)
			free(token_list->quote_map);
		free(token_list);
		token_list = tmp;
	}
}

t_token_type	get_token_type(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len == 1 && str[0] == '|')
		return (PIPE);
	if (len == 1 && str[0] == '<')
		return (REDIR_IN);
	if (len == 1 && str[0] == '>')
		return (REDIR_OUT);
	if (len == 1 && str[0] == '(')
		return (OPEN_PAREN);
	if (len == 1 && str[0] == ')')
		return (CLOSE_PAREN);
	if (len == 2 && str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	if (len == 2 && str[0] == '>' && str[1] == '>')
		return (APPEND);
	if (len == 2 && str[0] == '&' && str[1] == '&')
		return (LOGICAL_AND);
	if (len == 2 && str[0] == '|' && str[1] == '|')
		return (LOGICAL_OR);
	return (WORD);
}

void	init_token(t_token *token)
{
	token->error = 0;
	token->type = WORD;
	token->value = NULL;
	token->quote_map = NULL;
	token->heredoc_expand = FALSE;
	token->expanded = FALSE;
	token->next = NULL;
}

t_token	*fetch_token(char **input)
{
	t_token	*token;

	if (!input || !*input)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	init_token(token);
	while (ft_isspace(**input))
		(*input)++;
	extract_token_value(input, token);
	if (!token->value)
		return (free(token), NULL);
	token->type = get_token_type(token->value);
	while (ft_isspace(**input))
		(*input)++;
	return (token);
}
