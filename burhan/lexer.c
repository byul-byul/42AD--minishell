/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:10:19 by bhajili           #+#    #+#             */
/*   Updated: 2025/03/10 10:19:33 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*ft_strndup(const char *s, size_t n)
{
	char			*res;
	unsigned int	i;

	i = 0;
	res = malloc(sizeof(char) * (n + 1));
	if (res == NULL)
		return (NULL);
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

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
	if (!strcmp(value, "|"))
		return (PIPE);
	if (!strcmp(value, "<"))
		return (REDIR_IN);
	if (!strcmp(value, ">"))
		return (REDIR_OUT);
	if (!strcmp(value, "<<"))
		return (HEREDOC);
	if (!strcmp(value, ">>"))
		return (APPEND);
	if (!strcmp(value, "&&"))
		return (LOGICAL_AND);
	if (!strcmp(value, "||"))
		return (LOGICAL_OR);
	return (0);
}

t_token	*create_token(const char *input, int *index)
{
	int		start;
	t_token	*token;

	while (input[*index] && input[*index] == ' ')
		(*index)++;
	start = *index;
	while (input[*index] && input[*index] != ' ')
		(*index)++;
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = ft_strndup(&input[start], *index - start);
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
