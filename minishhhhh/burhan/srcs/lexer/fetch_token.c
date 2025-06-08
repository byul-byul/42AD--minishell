/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/15 13:40:31 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static int	is_word_token_type(t_token_type type)
{
	return (WORD == type);
}

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
	token->next = NULL;
	token->quoted = FALSE;
	token->expanded = FALSE;
	token->heredoc_expand = FALSE;
}

static void	define_token_type(t_token *token, int exit_status)
{
	char	*tmp;

	token->type = get_token_type(token->value);
	if (is_word_token_type(token->type))
	{
		tmp = token->value;
		token->value = expand_token_value(token->value, exit_status);
		free(tmp);
		token->type = get_token_type(token->value);
	}
}

t_token	*fetch_token(char **input, t_token *prev_token, int exit_status)
{
	t_token	*token;

	while (ft_iswhitespace(**input))
		(*input)++;
	if (!**input)
		return (NULL);
	token = malloc(sizeof(t_token));
	if (token)
	{
		init_token(token);
		extract_to_token(token, input);
		if (!token->value)
			return (free(token), NULL);
		define_token_type(token, exit_status);
		if (prev_token && prev_token->type == HEREDOC)
			if (!(token->quoted && token->value[0] == '\''))
				token->heredoc_expand = TRUE;
	}
	return (token);
}
