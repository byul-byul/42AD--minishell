/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:19:08 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/18 01:20:38 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor_wrapper.h"

static int	exec_external(char **argv)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		setup_child_signals();
		// TODO: convert env to char **envp
		execve(argv[0], argv, NULL);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else
		g_exit_status = 1;
	return (g_exit_status);
}

int	exec_command(t_command *cmd)
{
	int	is_builtin_cmd;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	is_builtin_cmd = is_builtin(cmd->argv[0]);
	if (apply_redirections(cmd->redirections) != 0)
		return (1);
	if (is_builtin_cmd)
	{
		g_exit_status = exec_builtin(cmd->argv);
		restore_std_fds();
		return (g_exit_status);
	}
	restore_std_fds(); // Only needed if we later apply redirs in child too
	return (exec_external(cmd->argv));
}

int	exec_ast(t_ast_node *node)
{
	if (!node)
		return (0);
	if (node->type == NODE_COMMAND)
		return (exec_command(node->command));
	else if (node->type == NODE_PIPE)
		return (exec_pipe(node->left, node->right));
	else if (node->type == NODE_AND)
		return (exec_and(node->left, node->right));
	else if (node->type == NODE_OR)
		return (exec_or(node->left, node->right));
	else if (node->type == NODE_SUBSHELL)
		return (exec_subshell(node->left));
	return (1);
}
