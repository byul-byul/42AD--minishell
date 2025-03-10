/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:10:19 by bhajili           #+#    #+#             */
/*   Updated: 2025/03/10 15:18:12 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

int	identify_token_type(const char *value)
{
	if (!value)
		return (0);
	if (!ft_strcmp(value, "|"))
		return (PIPE);
	if (!ft_strcmp(value, "<"))
		return (REDIR_IN);
	if (!ft_strcmp(value, ">"))
		return (REDIR_OUT);
	if (!ft_strcmp(value, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(value, ">>"))
		return (APPEND);
	if (!ft_strcmp(value, "&&"))
		return (LOGICAL_AND);
	if (!ft_strcmp(value, "||"))
		return (LOGICAL_OR);
	return (0);
}

int	is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

void	define_token(const char *input, int *index)
{
	char	quote;

	quote = 0;
	while (input[*index] && (quote || (!is_operator(input[*index]) && input[*index] != ' ')))
	{
		if (input[*index] == '\\' && input[*index + 1])
		{
			(*index)++; // Пропускаем `\`, но переходим на следующий символ
		}
		else if (!quote && (input[*index] == '"' || input[*index] == '\''))
			quote = input[*index]; // Открываем кавычки
		else if (quote && input[*index] == quote)
			quote = 0; // Закрываем кавычки
		(*index)++;
	}
}

void	handle_operator(const char *input, int *i)
{
	if (is_operator(input[*i + 1]) && input[*i] == input[*i + 1])
		(*i) += 2;
	else
		(*i)++;
}

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && input[*i] == ' ')
		(*i)++;
}

t_token	*create_token(const char *input, int *i)
{
	t_token	*token;
	int		start;

	skip_spaces(input, i);
	start = *i;
	if (is_operator(input[*i]))
		handle_operator(input, i);
	else
		define_token(input, i);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strndup(&input[start], *i - start);
	token->type = identify_token_type(token->value);
	token->next = NULL;
	return (token);
}

t_token	*split_into_tokens(const char *input)
{
	int		i;
	t_token	*head;
	t_token	*new_token;

	i = 0;
	head = NULL;
	while (input[i])
	{
		new_token = create_token(input, &i);
		if (!new_token)
			return (free_tokens(head), NULL);
		add_token(&head, new_token);
	}
	return (head);
}

t_token	*lexer(const char *input)
{
	if (!input || !*input)
		return (NULL);
	return (split_into_tokens(input));
}
