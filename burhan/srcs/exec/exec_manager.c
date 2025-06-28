/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:19:08 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/28 14:10:34 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

int	exec_and(t_ast_node *left, t_ast_node *right, t_env *env)
{
	int	status;

	status = exec_ast(left, env);
	if (status == 0)
		return (exec_ast(right, env));
	return (status);
}

int	exec_or(t_ast_node *left, t_ast_node *right, t_env *env)
{
	int	status;

	status = exec_ast(left, env);
	if (status != 0)
		return (exec_ast(right, env));
	return (status);
}

int	exec_subshell(t_ast_node *node, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		int code = exec_ast(node, env);
		exit(code);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

int	exec_ast(t_ast_node *node, t_env *env)
{
	if (!node)
		return (1);
	if (node->type == NODE_COMMAND)
		return (exec_command(node->command, env));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(node->left, node->right, env));
	else if (node->type == NODE_AND)
		return (exec_and(node->left, node->right, env));
	else if (node->type == NODE_OR)
		return (exec_or(node->left, node->right, env));
	else if (node->type == NODE_SUBSHELL)
		return (exec_subshell(node->left, env));
	return (0);
}
