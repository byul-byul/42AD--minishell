/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/14 20:12:23 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lexer.h"
#include <stdlib.h>
#include <string.h>

static char	*expand_variables(char *str)
{
	int		i;
	int		j;
	char	buffer[EXPAND_BUFFER_SIZE];
	char	quote;

	i = -1;
	j = 0;
	quote = 0;
	while (str[++i])
		handle_variable_char(buffer, str, &i, &quote, &j);
	buffer[j] = '\0';
	return(ft_strdup(buffer));
}

static t_token_type	get_token_type(char *str, size_t len)
{
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

void	find_token_end(char *input, int *i)
{
	char	quote;

	if (is_metachar(input[*i]))
		(*i)++;
	else
	{
		while (input[*i] && !is_whitespace(input[*i]) && !is_metachar(input[*i]))
		{
			if (input[*i] == '\'' || input[*i] == '"')
			{
				quote = input[*i];
				(*i)++;
				while (input[*i] && input[*i] != quote)
					(*i)++;
				if (input[*i] == quote)
					(*i)++;
			}
			else
				(*i)++;
		}
	}
}

t_token	*fetch_token(char *input, int *i)
{
	int		start;
	char	*tmp;
	t_token	*token;

	while (is_whitespace(input[*i]))
		(*i)++;
	start = *i;
	find_token_end(input, i);
	token = malloc(sizeof(t_token));
	if (token)
	{
		tmp = ft_strndup(input + start, *i - start);
		if (tmp)
		{
			token->value = expand_variables(tmp);
			free(tmp);
			token->type = get_token_type(input + start, *i - start);
		}
	}
	return (token);
}

t_token	*lexer(char *input)
{
	int		i;
	int		j;
	t_token	token_list[TOKEN_LIST_SIZE];

	i = -1;
	j = 0;
	if (input)
	{
		while (1)
		{
			token = fetch_token_value(&input);
			token_list[j].value = fetch_token_value(&input);
			token_list[j].type = define_token_type(token_list[j].value);
		}
	}
	return (token_list);
}

// t_token	*lexer(char *input)
// {
// 	int		i;
// 	t_token	*token;
// 	t_token	*token_list;

// 	i = -1;
// 	token_list = NULL;
// 	if (input)
// 	{
// 		while (input[++i])
// 		{
// 			token = fetch_token(input, &i);
// 			if (!token->value)
// 				break ;
// 			add_token(&token_list, token);
// 		}
// 	}
// 	return (token_list);
// }
