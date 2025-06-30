/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:56:39 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/30 23:12:46 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

t_redir	*parse_redirection(t_token **token_list)
{
	t_redir	*redir;
	t_token	*op;
	t_token	*file;

	op = *token_list;
	*token_list = (*token_list)->next;
	if (!*token_list || (*token_list)->type != WORD)
	{
		print_parser_error("Syntax error near unexpected token", op->value);
		return (NULL);
	}
	file = *token_list;
	*token_list = (*token_list)->next;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = op->type;
	redir->filename = ft_strdup(file->value);
	return (redir);
}

void	add_redir_back(t_redir **redir_list, t_redir *new_redir)
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

char	**list_to_str_array(t_list *list)
{
	int		size;
	char	**array;
	int		i;

	size = ft_lstsize(list);
	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (list)
	{
		array[i++] = ft_strdup((char *)list->content);
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

t_command	*parse_simple_command(t_token **token_list)
{
	t_command	*cmd;
	t_list		*argv_list;
	t_redir		*redir;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	argv_list = NULL;
	cmd->redirections = NULL;

	while (*token_list)
	{
		if ((*token_list)->type == WORD)
		{
			ft_lstadd_back(&argv_list, ft_lstnew(ft_strdup((*token_list)->value)));
			*token_list = (*token_list)->next;
		}
		else if (is_redirect_token((*token_list)->type))
		{
			redir = parse_redirection(token_list);
			if (!redir)
			{
				free_command(cmd);
				ft_lstclear(&argv_list, free);
				return (NULL);
			}
			add_redir_back(&cmd->redirections, redir);
		}
		else
			break;
	}
	cmd->argv = list_to_str_array(argv_list);
	ft_lstclear(&argv_list, free);
	if (!cmd->argv || !cmd->argv[0])
	{
		free_command(cmd);
		print_parser_error("Expected command", NULL);
		return (NULL);
	}
	return (cmd);
}


t_ast_node	*parse_subshell(t_token **token_list)
{
	t_ast_node	*subtree;
	t_ast_node	*node;

	if (!*token_list || (*token_list)->type != OPEN_PAREN)
	{
		print_parser_error("Expected '('", NULL);
		return (NULL);
	}
	*token_list = (*token_list)->next;
	subtree = parse_logical_or(token_list);
	if (!subtree)
		return (NULL);
	if (!*token_list || (*token_list)->type != CLOSE_PAREN)
	{
		print_parser_error("Expected ')'", NULL);
		free_ast(subtree);
		return (NULL);
	}
	*token_list = (*token_list)->next;

	node = create_ast_node(NODE_SUBSHELL, subtree, NULL);
	return (node);
}

t_ast_node	*parse_command(t_token **token_list)
{
	t_command	*cmd;
	t_ast_node	*node;

	if (*token_list && (*token_list)->type == OPEN_PAREN)
		return (parse_subshell(token_list));

	cmd = parse_simple_command(token_list);
	if (!cmd)
		return (NULL);

	node = create_ast_node(NODE_COMMAND, NULL, NULL);
	node->command = cmd;
	return (node);
}

t_ast_node	*parse_pipe(t_token **token_list)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = parse_command(token_list);
	if (!left)
		return (NULL);
	while (*token_list && (*token_list)->type == PIPE)
	{
		*token_list = (*token_list)->next;
		right = parse_command(token_list);
		if (!right)
		{
			print_parser_error("Syntax error near unexpected token '|'", NULL);
			free_ast(left);
			return (NULL);
		}
		left = create_ast_node(NODE_PIPE, left, right);
	}
	return (left);
}

t_ast_node	*parse_logical_and(t_token **token_list)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = parse_pipe(token_list);
	if (!left)
		return (NULL);
	while (*token_list && (*token_list)->type == LOGICAL_AND)
	{
		*token_list = (*token_list)->next;
		right = parse_pipe(token_list);
		if (!right)
		{
			print_parser_error("Syntax error near unexpected token '&&'", NULL);
			free_ast(left);
			return (NULL);
		}
		left = create_ast_node(NODE_AND, left, right);
	}
	return (left);
}

t_ast_node	*parse_logical_or(t_token **token_list)
{
	t_ast_node	*left;
	t_ast_node	*right;

	left = parse_logical_and(token_list);
	if (!left)
		return (NULL);
	while (*token_list && (*token_list)->type == LOGICAL_OR)
	{
		*token_list = (*token_list)->next;
		right = parse_logical_and(token_list);
		if (!right)
		{
			print_parser_error("Syntax error near unexpected token '||'", NULL);
			free_ast(left);
			return (NULL);
		}
		left = create_ast_node(NODE_OR, left, right);
	}
	return (left);
}

t_ast_node	*parser(t_token *token_list)
{
	t_ast_node	*ast;
	t_token 	*current;

	if (!token_list)
		return (NULL);
	current = token_list;
	ast = parse_logical_or(&current);
	if (current)
	{
		print_parser_error("Syntax error near unexpected token", current->value);
		if (ast)
		{
			free_ast(ast);
			ast = NULL;
		}
	}
	return (ast);
}
