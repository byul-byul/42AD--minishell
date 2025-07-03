/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:19:08 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 18:31:22 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

// int	handle_and_return_status(int status)
// {
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	else if (WIFSIGNALED(status))
// 	{
// 		g_exit_status = 128 + WTERMSIG(status);
// 		return (g_exit_status);
// 	}
// 	return (1);
// }

int	handle_and_return_status(int status)
{
	int	sig;

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (sig == SIGQUIT)
			write(STDOUT_FILENO, "Quit: 3\n", 8);
		g_exit_status = 128 + sig;
		return (g_exit_status);
	}
	return (1);
}

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
	int		code;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		code = exec_ast(node, env);
		exit(code);
	}
	waitpid(pid, &status, 0);
	return (handle_and_return_status(status));
}

int	exec_ast(t_ast_node *node, t_env *env)
{
	if (!node)
		return (1);
	if (node->type == NODE_COMMAND)
	{
		if (handle_heredocs(node->command))
			return (1);
		return (exec_command(node->command, env));
	}
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
