/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:56:39 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 16:18:27 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

static t_redir	*parse_redirection(t_token **token_list)
{
	t_redir	*redir;
	t_token	*op;
	t_token	*file;

	op = *token_list;
	*token_list = (*token_list)->next;
	if (!*token_list || (*token_list)->type != WORD)
	{
		print_parser_error(ERR_CODE_PARSER_SYNTAX_00, op->value);
		return (NULL);
	}
	file = *token_list;
	*token_list = (*token_list)->next;
	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = op->type;
	redir->filename = ft_strdup(file->value);
	redir->heredoc_expand = file->heredoc_expand;
	return (redir);
}

static void	add_redir_back(t_redir **redir_list, t_redir *new_redir)
{
	t_redir	*curr;

	if (!redir_list || !new_redir)
		return ;
	if (!*redir_list)
	{
		*redir_list = new_redir;
		return ;
	}
	curr = *redir_list;
	while (curr->next)
		curr = curr->next;
	curr->next = new_redir;
}

int	parse_args_and_redirs(t_token **tl, t_list **argv, t_command *cmd)
{
	t_redir	*redir;

	while (*tl)
	{
		if ((*tl)->type == WORD)
		{
			ft_lstadd_back(argv, ft_lstnew(ft_strdup((*tl)->value)));
			*tl = (*tl)->next;
		}
		else if (is_redirect_token((*tl)->type))
		{
			redir = parse_redirection(tl);
			if (!redir)
				return (1);
			add_redir_back(&cmd->redirections, redir);
		}
		else
			break ;
	}
	return (0);
}
