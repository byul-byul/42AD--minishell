/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils_00.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 14:53:27 by bhajili          ###   ########.fr       */
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

t_token_type	get_token_type(char *value, char *quote_map)
{
	size_t	len;

	if (quote_map)
		if (ft_strchr(quote_map, '1') || ft_strchr(quote_map, '2'))
			return (WORD);
	len = ft_strlen(value);
	if (len == 1 && value[0] == '|')
		return (PIPE);
	if (len == 1 && value[0] == '<')
		return (REDIR_IN);
	if (len == 1 && value[0] == '>')
		return (REDIR_OUT);
	if (len == 1 && value[0] == '(')
		return (OPEN_PAREN);
	if (len == 1 && value[0] == ')')
		return (CLOSE_PAREN);
	if (len == 2 && value[0] == '<' && value[1] == '<')
		return (HEREDOC);
	if (len == 2 && value[0] == '>' && value[1] == '>')
		return (APPEND);
	if (len == 2 && value[0] == '&' && value[1] == '&')
		return (LOGICAL_AND);
	if (len == 2 && value[0] == '|' && value[1] == '|')
		return (LOGICAL_OR);
	return (WORD);
}

static void	init_token(t_token *token)
{
	token->type = WORD;
	token->value = NULL;
	token->quote_map = NULL;
	token->heredoc_expand = FALSE;
	token->expanded = FALSE;
	token->next = NULL;
}

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	init_token(token);
	token->type = type;
	token->value = ft_strdup(value);
	return (token);
}

t_token	*fetch_token(char **input)
{
	t_token	*token;

	if (!input || !*input)
		return (NULL);
	token = create_token(WORD, NULL);
	if (!token)
		return (NULL);
	while (ft_isspace(**input))
		(*input)++;
	extract_token_value(input, token);
	if (!token->value)
		return (free(token), NULL);
	token->type = get_token_type(token->value, token->quote_map);
	while (ft_isspace(**input))
		(*input)++;
	return (token);
}
