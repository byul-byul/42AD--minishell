/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:19:08 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/25 21:09:42 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

int	exec_subshell(t_ast_node *node)
{
	(void)node;
	ft_putstr("exec_subshell(): MOCK was launced\n");
	return (1);
}

int	exec_or(t_ast_node *left, t_ast_node *right)
{
	(void)left;
	(void)right;
	ft_putstr("exec_or(): MOCK was launced\n");
	return (1);
}

int	exec_and(t_ast_node *left, t_ast_node *right)
{
	(void)left;
	(void)right;
	ft_putstr("exec_and(): MOCK was launced\n");
	return (1);
}

int	exec_pipe(t_ast_node *left, t_ast_node *right)
{
	(void)left;
	(void)right;
	ft_putstr("exec_pipe(): MOCK was launced\n");
	return (1);
}

int	exec_ast(t_ast_node *node, t_env *env)
{
	if (!node)
		return (1);
	if (node->type == NODE_COMMAND)
		return (exec_command(node->command, env));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(node->left, node->right));
	else if (node->type == NODE_AND)
		return (exec_and(node->left, node->right));
	else if (node->type == NODE_OR)
		return (exec_or(node->left, node->right));
	else if (node->type == NODE_SUBSHELL)
		return (exec_subshell(node->left));
	return (0);
}
