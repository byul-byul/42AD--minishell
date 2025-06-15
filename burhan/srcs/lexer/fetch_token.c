/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/15 12:31:02 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static t_token_type	get_token_type(char *str)
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

static void	init_token(t_token *token)
{
	token->error = 0;
	token->value = NULL;
	token->type = WORD;
	token->quoted = NONE;
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
