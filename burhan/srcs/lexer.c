/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/15 01:11:51 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/lexer.h"

void	clean_token_list(t_token *token_list)
{
	t_token	*tmp;

	while (token_list)
	{
		tmp = token_list->next;
		free(token_list->value);
		free(token_list);
		token_list = tmp;
	}
}

static int	is_word_type_token(t_token_type type)
{
	return (WORD == type);
}

int	is_metachar(char c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
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

char	*expand_value(const char *value, int last_exit_status)
{
	char	*result;
	char	*tmp;
	size_t	i;

	result = ft_strdup("");
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1])
		{
			if (value[i + 1] == '?')
			{
				tmp = result;
				result = ft_strjoin(result, ft_itoa(last_exit_status));
				free(tmp);
				i += 2;
			}
			else if (ft_isalpha(value[i + 1]) || value[i + 1] == '_')
			{
				size_t	start = i + 1;
				while (ft_isalnum(value[i + 1]) || value[i + 1] == '_')
					i++;
				tmp = ft_substr(value, start, i - start + 1);
				char *env_value = getenv(tmp);
				free(tmp);
				tmp = result;
				result = ft_strjoin(result, env_value ? env_value : "");
				free(tmp);
				i++;
			}
			else
			{
				tmp = result;
				result = ft_strjoin(result, "$");
				free(tmp);
				i++;
			}
		}
		else
		{
			tmp = result;
			result = ft_strjoin(result, (char[]){value[i], '\0'});
			free(tmp);
			i++;
		}
	}
	return (result);
}

void	extract_to_token(t_token *token, char **input)
{
	char	quote;
	char	*start;

	start = *input;
	if (is_metachar(**input))
	{
		if (((**input == '|' || **input == '&' || **input == '<' || **input == '>'))
			&& (*(*input + 1) == **input))
		// if (!is_word_type_token(get_token_type(*input)))
			(*input)++; // захватываем второй символ для ||, &&, <<, >>
		(*input)++;
	}
	else
	{
		while (**input && !ft_iswhitespace(**input) && !is_metachar(**input))
		{
			if (**input == '\'' || **input == '"')
			{
				quote = **input;
				(*input)++;
				while (**input && **input != quote)
					(*input)++;
				if (**input == quote)
				{
					token->quoted = TRUE;
					(*input)++;
				}
				else
				{
					token->value = NULL;
					return ;
				}
			}
			else
				(*input)++;
		}
	}
	token->value = ft_strndup(start, *input - start);
}

static void	init_token(t_token *token)
{
	token->next = NULL;
	token->quoted = FALSE;
	token->expanded = FALSE;
	token->heredoc_expand = FALSE;
}

t_token	*fetch_token(char **input, t_token *prev_token, int exit_status)
{
	t_token	*token;
	char	*tmp;

	token = malloc(sizeof(t_token));
	if (token)
	{
		init_token(token);
		while (ft_iswhitespace(**input))
			(*input)++;
		extract_to_token(token, input);
		if (!token->value)
			return (free(token), NULL);
		token->type = get_token_type(token->value);
		if (is_word_type_token(token->type))
		{
			tmp = token->value;
			token->value = expand_value(token->value, exit_status);
			free(tmp);
			token->type = get_token_type(token->value);
		}
		if (prev_token && prev_token->type == HEREDOC)
			if (!(token->quoted && token->value[0] == '\''))
				token->heredoc_expand = TRUE;
	}
	return (token);
}

t_token	*lexer(char *input, int exit_status)
{
	t_token	*new_token;
	t_token	*last_token;
	t_token	*token_list;

	new_token = fetch_token(&input, NULL, exit_status);
	if (!new_token)
		return (NULL);
	token_list = new_token;
	last_token = new_token;
	while (1)
	{
		new_token = fetch_token(&input, last_token, exit_status);
		if (!new_token)
			return (clean_token_list(token_list), NULL);
		last_token->next = new_token;
		last_token = new_token;
		if (!*input)
			break ;
	}
	return (token_list);
}
