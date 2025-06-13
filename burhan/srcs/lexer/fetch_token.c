/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/14 02:47:16 by bhajili          ###   ########.fr       */
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

static void	define_token_type(t_token *token, int exit_status)
{
	char	*tmp;
	char	*expanded;

	token->type = get_token_type(token->value);
	if (token->type == WORD)
	{
		tmp = token->value;
		expanded = expand_token_value(token->value, token->quoted, exit_status);
		token->expanded = (expanded && ft_strcmp(tmp, expanded) != 0);
		token->value = expanded;
		free(tmp);
		token->type = get_token_type(token->value);
	}
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

t_token	*fetch_token(char **input, int exit_status)
{
	t_token	*token;

	if (!input || !*input)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	init_token(token);
	while (ft_iswhitespace(**input))
		(*input)++;
	extract_token_value(input, token);
	if (!token->value)
		return (free(token), NULL);
	define_token_type(token, exit_status);
	while (ft_iswhitespace(**input))
		(*input)++;
	return (token);
}
