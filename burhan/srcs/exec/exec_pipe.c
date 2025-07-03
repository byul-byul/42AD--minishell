/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:06:59 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 07:11:28 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

static void	child_writer(t_ast_node *left, int *pipefd, t_env *env)
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(exec_ast(left, env));
}

static void	child_reader(t_ast_node *right, int *pipefd, t_env *env)
{
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	exit(exec_ast(right, env));
}

int	exec_pipe(t_ast_node *left, t_ast_node *right, t_env *env)
{
	int		pipefd[2];
	pid_t	pid_left;
	pid_t	pid_right;
	int		status;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	fcntl(pipefd[0], F_SETFD, FD_CLOEXEC);
	fcntl(pipefd[1], F_SETFD, FD_CLOEXEC);
	pid_left = fork();
	if (pid_left == 0)
		child_writer(left, pipefd, env);
	pid_right = fork();
	if (pid_right == 0)
		child_reader(right, pipefd, env);
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);
	return (handle_and_return_status(status));
}
