/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 19:51:22 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 19:41:11 by bhajili          ###   ########.fr       */
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

static void	swap_fd(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

int	exec_command(t_command *cmd, t_env *env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;

	if (!cmd)
		return (1);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (apply_redirections(cmd->redirections) == -1)
	{
		swap_fd(saved_stdin, saved_stdout);
		return (1);
	}
	if (cmd->argv && cmd->argv[0])
	{
		if (is_builtin(cmd->argv[0]))
			status = exec_builtin(cmd, env);
		else
			status = exec_external(cmd, env);
	}
	else
		status = 0;
	swap_fd(saved_stdin, saved_stdout);
	return (status);
}
