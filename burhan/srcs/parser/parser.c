/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:56:39 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/28 21:35:33 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

// t_redir	*parse_redirection(t_token **token_list)
// {
// 	t_redir	*redir;
// 	t_token_type	type;
// 	char	*filename;

// 	if (!*token_list || !is_redirect_token((*token_list)->type))
// 		return (NULL);
// 	type = (*token_list)->type;
// 	*token_list = (*token_list)->next;

// 	// Проверка на отсутствие аргумента после редиректа
// 	if (!*token_list || (*token_list)->type != WORD)
// 	{
// 		parser_error("Syntax error: expected filename after redirection", NULL);
// 		return (NULL);
// 	}
// 	filename = ft_strdup((*token_list)->value);
// 	if (!filename)
// 		return (NULL);

// 	redir = ft_calloc(1, sizeof(t_redir));
// 	if (!redir)
// 	{
// 		free(filename);
// 		return (NULL);
// 	}
// 	redir->type = type;
// 	redir->filename = filename;
// 	redir->heredoc_expand = (type == HEREDOC && !is_quoted(filename));
// 	redir->next = NULL;

// 	*token_list = (*token_list)->next;
// 	return (redir);
// }

t_command	*parse_simple_command(t_token **token_list)
{
	t_command	*cmd;

	if (!*token_list || (*token_list)->type != WORD)
	{
		parser_error("Expected command", NULL);
		return (NULL);
	}

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);

	cmd->argv = ft_calloc(2, sizeof(char *)); // один аргумент + NULL
	if (!cmd->argv)
	{
		free(cmd);
		return (NULL);
	}
	cmd->argv[0] = ft_strdup((*token_list)->value);
	cmd->argv[1] = NULL;

	*token_list = (*token_list)->next;
	return (cmd);
}

t_ast_node	*parse_subshell(t_token **token_list)
{
	t_ast_node	*subtree;
	t_ast_node	*node;

	// Проверка на открывающую скобку
	if (!*token_list || (*token_list)->type != OPEN_PAREN)
	{
		parser_error("Expected '('", NULL);
		return (NULL);
	}
	*token_list = (*token_list)->next; // съедаем "("

	// Рекурсивно парсим всё внутри скобок
	subtree = parse_logical_or(token_list);
	if (!subtree)
		return (NULL);

	// После содержимого ожидается закрывающая скобка
	if (!*token_list || (*token_list)->type != CLOSE_PAREN)
	{
		parser_error("Expected ')'", NULL);
		free_ast(subtree);
		return (NULL);
	}
	*token_list = (*token_list)->next; // съедаем ")"

	// Оборачиваем поддерево в NODE_SUBSHELL
	node = create_ast_node(NODE_SUBSHELL, subtree, NULL);
	return (node);
}

t_ast_node	*parse_command(t_token **token_list)
{
	t_command	*cmd;
	t_ast_node	*node;

	// Проверяем на подскобку: ( ... )
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
		*token_list = (*token_list)->next; // съедаем "|"
		right = parse_command(token_list);
		if (!right)
		{
			parser_error("Syntax error near unexpected token '|'", NULL);
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
		*token_list = (*token_list)->next; // съедаем "&&"
		right = parse_pipe(token_list);
		if (!right)
		{
			parser_error("Syntax error near unexpected token '&&'", NULL);
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
		*token_list = (*token_list)->next; // съедаем "||"
		right = parse_logical_and(token_list);
		if (!right)
		{
			parser_error("Syntax error near unexpected token '||'", NULL);
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
	// Начинаем разбор с самого низкоприоритетного оператора (||)
	ast = parse_logical_or(&current);
	// Проверка на остаточные токены (мусор после корректного парсинга)
	if (current)
	{
		// Ошибка: неожиданные токены после команды
		parser_error("Syntax error near unexpected token", current->value);
		if (ast)
		{
			free_ast(ast);
			ast = NULL;
		}
	}
	return (ast);
}
