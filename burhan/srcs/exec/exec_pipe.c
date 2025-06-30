/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:06:59 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/30 14:15:57 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

int	exec_pipe(t_ast_node *left, t_ast_node *right, t_env *env)
{
	int		pipefd[2];
	pid_t	pid_left, pid_right;
	int		status = 1;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);

	// Set CLOEXEC so any execve() in children auto-closes the pipe ends
	fcntl(pipefd[0], F_SETFD, FD_CLOEXEC);
	fcntl(pipefd[1], F_SETFD, FD_CLOEXEC);

	pid_left = fork();
	if (pid_left == -1)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), 1);
	if (pid_left == 0)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(exec_ast(left, env));
	}

	pid_right = fork();
	if (pid_right == -1)
		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), 1);
	if (pid_right == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		exit(exec_ast(right, env));
	}

	close(pipefd[0]);
	close(pipefd[1]);

	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &status, 0);

	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}

// int	exec_pipe(t_ast_node *left, t_ast_node *right, t_env *env)
// {
// 	int		pipefd[2];
// 	pid_t	pid1, pid2;
// 	int		status = 1;

// 	if (pipe(pipefd) == -1)
// 		return (perror("pipe"), 1);
// 	pid1 = fork();
// 	if (pid1 == -1)
// 		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), 1);
// 	if (pid1 == 0)
// 	{
// 		dup2(pipefd[1], STDOUT_FILENO);
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		exit(exec_ast(left, env));
// 	}
// 	pid2 = fork();
// 	if (pid2 == -1)
// 		return (perror("fork"), close(pipefd[0]), close(pipefd[1]), 1);
// 	if (pid2 == 0)
// 	{
// 		dup2(pipefd[0], STDIN_FILENO);
// 		close(pipefd[0]);
// 		close(pipefd[1]);
// 		exit(exec_ast(right, env));
// 	}
// 	close(pipefd[0]);
// 	close(pipefd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, &status, 0);
// 	if (WIFEXITED(status))
// 		return (WEXITSTATUS(status));
// 	return (1);
// }
