/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 04:51:33 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 10:26:45 by bhajili          ###   ########.fr       */
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

	signal(SIGQUIT, SIG_DFL);
	setup_child_signals();
	envp = env_reassemble_envp(env);
	execve(path, cmd->argv, envp);
	perror("execve");
	exit(126);
}

static int	print_error_and_return_status(char *argvalue)
{
	if (ft_strchr(argvalue, '/'))
		print_exec_error(argvalue, "No such file or directory");
	else
		print_exec_error(argvalue, "command not found");
	return (127);
}

int	exec_external(t_command *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	*path;

	if (!cmd || !cmd->argv || !cmd->argv[0][0])
		return (print_exec_error(cmd->argv[0], "command not found"), 127);
	path = resolve_path(cmd->argv[0], env);
	if (!path)
		return (print_error_and_return_status(cmd->argv[0]));
	pid = fork();
	if (pid == -1)
		return (perror("fork"), free(path), 1);
	if (pid == 0)
		handle_child_exec(path, cmd, env);
	free(path);
	waitpid(pid, &status, 0);
	return (handle_and_return_status(status));
}
