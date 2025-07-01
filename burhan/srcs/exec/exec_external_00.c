/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 04:51:33 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/01 03:20:24 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

void	print_exec_error(const char *cmd, const char *msg)
{
	if (cmd)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	ft_putstr_fd("\n", 2);
}

static int	handle_child_exec(char *path, t_command *cmd, t_env *env)
{
	char	**envp;

	envp = env_reassemble_envp(env);
	execve(path, cmd->argv, envp);
	perror("execve");
	exit(126);
}

int	exec_external(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path;

	path = resolve_path(cmd->argv[0], env);
	if (!path)
	{
		print_exec_error(cmd->argv[0], "command not found");
		return (127);
	}
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(path), 1);
	if (pid == 0)
		handle_child_exec(path, cmd, env);
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
