/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:51:22 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 16:30:25 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

int	open_redir_file(t_redir *redir)
{
	int	fd;

	if (!redir || !redir->filename)
		return (-1);
	if (redir->type == REDIR_IN)
		fd = open(redir->filename, O_RDONLY);
	else if (redir->type == REDIR_OUT)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (redir->type == HEREDOC)
		return (redir->fd);
	else
		return (-1);
	if (fd < 0)
		perror(redir->filename);
	return (fd);
}

int	apply_redirections(t_redir *redir_list)
{
	t_redir	*curr;
	int		fd;

	curr = redir_list;
	while (curr)
	{
		fd = open_redir_file(curr);
		if (fd < 0)
			return (1);
		if (curr->type == REDIR_IN || curr->type == HEREDOC)
			dup2(fd, STDIN_FILENO);
		else if (curr->type == REDIR_OUT || curr->type == APPEND)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		curr = curr->next;
	}
	return (0);
}

int	exec_command(t_command *cmd, t_env *env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (0);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redirections) == -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		return (1);
	}
	if (is_builtin(cmd->argv[0]))
		status = exec_builtin(cmd, env);
	else
		status = exec_external(cmd, env);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
	return (status);
}

// int	exec_command(t_command *cmd, t_env *env)
// {
// 	if (!cmd || !cmd->argv || !cmd->argv[0])
// 		return (0);
// 	if (apply_redirections(cmd->redirections) != 0)
// 		return (1);
// 	if (is_builtin(cmd->argv[0]))
// 		return (exec_builtin(cmd, env));
// 	else
// 		return (exec_external(cmd, env));
// }

// volatile sig_atomic_t	g_exit_status = 0;

// int	set_exit_status(int status)
// {
// 	g_exit_status = status;
// 	return (status);
// }

// int	apply_redirections(t_redir *redir_list)
// {
// 	(void)redir_list;
// 	ft_putstr("apply_redirections(): MOCK was launched\n");
// 	return (0);
// }

// void	restore_std_fds(void)
// {
// 	ft_putstr("restore_std_fds(): MOCK was launched\n");
// }

// int	is_builtin(const char *cmd)
// {
// 	(void)cmd;
// 	ft_putstr("is_builtin(): MOCK was launched\n");
// 	return (1);
// }

// int	exec_builtin(char **argv)
// {
// 	(void)argv;
// 	ft_putstr("exec_builtin(): MOCK was launched\n");
// 	return (0);
// }

// static int	exec_external(char **argv, t_env *env)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid < 0)
// 	{
// 		// perror("fork");
// 		return (set_exit_status(1));
// 	}
// 	if (pid == 0)
// 	{
// 		setup_child_signals();
// 		execve(argv[0], argv, env_reassemble_envp(env));
// 		// perror("execve");
// 		exit(127);
// 	}
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 		return (set_exit_status(WEXITSTATUS(status)));
// 	return (set_exit_status(1));
// }

// int	exec_command(t_command *cmd, t_env *env)
// {
// 	if (!cmd || !cmd->argv || !cmd->argv[0])
// 		return (set_exit_status(DEFAULT_STATUS));
// 	if (apply_redirections(cmd->redirections) != 0)
// 	{
// 		return (set_exit_status(REDIR_STATUS));
// 	}
// 	if (is_builtin(cmd->argv[0]))
// 	{
// 		g_exit_status = exec_builtin(cmd->argv);
// 		restore_std_fds();
// 		return (g_exit_status);
// 	}
// 	restore_std_fds();
// 	return (exec_external(cmd->argv, env));
// }
