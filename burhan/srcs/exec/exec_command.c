/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:51:22 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/26 12:48:50 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

int	set_exit_status(int status)
{
	g_exit_status = status;
	return (status);
}

int	apply_redirections(t_redir *redir_list)
{
	(void)redir_list;
	ft_putstr("apply_redirections(): MOCK was launched\n");
	return (0);
}

void	restore_std_fds(void)
{
	ft_putstr("restore_std_fds(): MOCK was launched\n");
}

int	is_builtin(const char *cmd)
{
	(void)cmd;
	ft_putstr("is_builtin(): MOCK was launched\n");
	return (1);
}

int	exec_builtin(char **argv)
{
	(void)argv;
	ft_putstr("exec_builtin(): MOCK was launched\n");
	return (0);
}

static int	exec_external(char **argv, t_env *env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		// perror("fork");
		return (set_exit_status(1));
	}
	if (pid == 0)
	{
		setup_child_signals();
		execve(argv[0], argv, env_reassemble_envp(env));
		// perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (set_exit_status(WEXITSTATUS(status)));
	return (set_exit_status(1));
}

int	exec_command(t_command *cmd, t_env *env)
{
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (set_exit_status(DEFAULT_STATUS));
	if (apply_redirections(cmd->redirections) != 0)
	{
		return (set_exit_status(REDIR_STATUS));
	}
	if (is_builtin(cmd->argv[0]))
	{
		g_exit_status = exec_builtin(cmd->argv);
		restore_std_fds();
		return (g_exit_status);
	}
	restore_std_fds();
	return (exec_external(cmd->argv, env));
}
