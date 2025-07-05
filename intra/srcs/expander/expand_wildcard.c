/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:40:53 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 19:34:52 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_wrapper.h"

static int	is_unquoted_wildcard(const char *val, const char *qmap)
{
	size_t	i;

	if (!val || !qmap)
		return (0);
	i = 0;
	while (val[i])
	{
		if (val[i] == '*' && qmap[i] != '1' && qmap[i] != '2')
			return (1);
		i++;
	}
	return (0);
}

static void	insert_token_list(t_token **head, t_token *curr,
				t_token *new_tokens)
{
	t_token	*last;
	t_token	*tmp;
	t_token	*prev;

	last = new_tokens;
	tmp = curr->next;
	while (last->next)
		last = last->next;
	last->next = tmp;
	if (*head == curr)
		*head = new_tokens;
	else
	{
		prev = *head;
		while (prev && prev->next != curr)
			prev = prev->next;
		if (prev)
			prev->next = new_tokens;
	}
}

int	match_and_insert(t_token **head, t_token *curr, const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_token			*new_tokens;

	new_tokens = NULL;
	dir = opendir(".");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_name[0] != '.' && fnmatch(pattern, entry->d_name, 0) == 0)
			tokenlist_push_back(&new_tokens, create_token(WORD, entry->d_name));
		entry = readdir(dir);
	}
	closedir(dir);
	if (!new_tokens)
		return (1);
	insert_token_list(head, curr, new_tokens);
	return (free(curr->value), free(curr->quote_map), free(curr), 1);
}

// int	handle_wildcard_expansion(t_token *token_list)
// {
// 	if (!token_list || !token_list->value || !token_list->quote_map)
// 		return (1);
// 	if (!is_unquoted_wildcard(token_list->value, token_list->quote_map))
// 		return (1);
// 	return (match_and_insert(&token_list, token_list, token_list->value));
// }

int	handle_wildcard_expansion(t_token **head, t_token *curr)
{
	if (!curr || !curr->value || !curr->quote_map)
		return (1);
	if (!is_unquoted_wildcard(curr->value, curr->quote_map))
		return (1);
	return (match_and_insert(head, curr, curr->value));
}
