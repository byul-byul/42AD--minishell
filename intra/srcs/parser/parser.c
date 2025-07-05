/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:56:39 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/04 20:34:42 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

static t_ast_node	*parse_pipe(t_token **token_list)
{
	t_ast_node	*left;
	t_ast_node	*right;

	if (!*token_list || (*token_list)->type == PIPE)
	{
		print_parser_error(ERR_CODE_PARSER_SYNTAX_00, (*token_list)->value);
		return (NULL);
	}
	left = parse_command(token_list);
	if (!left)
		return (NULL);
	while (*token_list && (*token_list)->type == PIPE)
	{
		*token_list = (*token_list)->next;
		right = parse_command(token_list);
		if (!right)
		{
			print_parser_error(ERR_CODE_PARSER_SYNTAX_00, "|");
			free_ast(left);
			return (NULL);
		}
		left = create_ast_node(NODE_PIPE, left, right);
	}
	return (left);
}

static t_ast_node	*parse_logical_and(t_token **token_list)
{
	t_ast_node	*left;
	t_ast_node	*right;

	if (!*token_list || (*token_list)->type == LOGICAL_AND)
	{
		print_parser_error(ERR_CODE_PARSER_SYNTAX_00, (*token_list)->value);
		return (NULL);
	}
	left = parse_pipe(token_list);
	if (!left)
		return (NULL);
	while (*token_list && (*token_list)->type == LOGICAL_AND)
	{
		*token_list = (*token_list)->next;
		right = parse_pipe(token_list);
		if (!right)
		{
			print_parser_error(ERR_CODE_PARSER_SYNTAX_00, "&&");
			free_ast(left);
			return (NULL);
		}
		left = create_ast_node(NODE_AND, left, right);
	}
	return (left);
}

static t_ast_node	*parse_logical_or(t_token **token_list)
{
	t_ast_node	*left;
	t_ast_node	*right;

	if (!*token_list)
		return (print_parser_error(ERR_CODE_PARSER_SYNTAX_00, "newline"), NULL);
	if ((*token_list)->type == LOGICAL_OR)
		return (print_parser_error(ERR_CODE_PARSER_SYNTAX_00, "||"), NULL);
	left = parse_logical_and(token_list);
	if (!left)
		return (NULL);
	while (*token_list && (*token_list)->type == LOGICAL_OR)
	{
		*token_list = (*token_list)->next;
		right = parse_logical_and(token_list);
		if (!right)
		{
			print_parser_error(ERR_CODE_PARSER_SYNTAX_00, "||");
			free_ast(left);
			return (NULL);
		}
		left = create_ast_node(NODE_OR, left, right);
	}
	return (left);
}

t_ast_node	*parse_subshell(t_token **token_list)
{
	t_ast_node	*subtree;
	t_ast_node	*node;

	if (!*token_list || (*token_list)->type != OPEN_PAREN)
		return (NULL);
	*token_list = (*token_list)->next;
	subtree = parse_logical_or(token_list);
	if (!subtree)
		return (NULL);
	if (!*token_list || (*token_list)->type != CLOSE_PAREN)
	{
		free_ast(subtree);
		return (NULL);
	}
	*token_list = (*token_list)->next;
	node = create_ast_node(NODE_SUBSHELL, subtree, NULL);
	return (node);
}

t_ast_node	*parser(t_token *token_list)
{
	t_ast_node	*ast;
	t_token		*current;

	if (!token_list)
		return (NULL);
	current = token_list;
	ast = parse_logical_or(&current);
	if (ast == NULL)
		return (NULL);
	if (current)
	{
		print_parser_error(ERR_CODE_PARSER_SYNTAX_00, current->value);
		if (ast)
		{
			free_ast(ast);
			ast = NULL;
		}
	}
	return (ast);
}
