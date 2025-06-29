/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 04:51:33 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 08:59:17 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

// static int	is_executable(char *path)
// {
// 	return (access(path, X_OK) == 0);
// }

char *resolve_path(const char *cmd_name, t_env *env)
{
	char	**paths;
	char	*full_path;
	int		i;
	char	*path_env;
	char	*parts[3];

	if (!cmd_name || !env)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (access(cmd_name, X_OK) == 0 ? ft_strdup(cmd_name) : NULL);
	path_env = env_getvalue(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		parts[0] = paths[i];
		parts[1] = (char *)cmd_name;
		full_path = ft_strjoin_charset(2, (const char **)parts, "/");
		if (!full_path)
			return (ft_freearr(paths, -1), NULL);
		if (access(full_path, X_OK) == 0)
			return (ft_freearr(paths, ft_arrsize(paths)), full_path);
		free(full_path);
		i++;
	}
	ft_freearr(paths, ft_arrsize(paths));
	return (NULL);
}

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
	{
		perror("fork");
		free(path);
		return (1);
	}
	if (pid == 0)
	{
		execve(path, cmd->argv, env_reassemble_envp(env));
		perror("execve");
		exit(126);
	}
	free(path);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
