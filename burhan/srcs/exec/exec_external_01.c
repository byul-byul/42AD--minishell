/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external_01.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 04:51:33 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/01 03:19:57 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

// static int	is_executable(char *path)
// {
// 	return (access(path, X_OK) == 0);
// }

static char	*check_direct_path(const char *cmd_name)
{
	if (access(cmd_name, X_OK) == 0)
		return (ft_strdup(cmd_name));
	return (NULL);
}

static char	*search_in_path(char **paths, const char *cmd_name)
{
	int		i;
	char	*full_path;
	char	*parts[3];

	i = 0;
	while (paths[i])
	{
		parts[0] = paths[i];
		parts[1] = (char *)cmd_name;
		full_path = ft_strjoin_charset(2, (const char **)parts, "/");
		if (!full_path)
		{
			ft_freearr(paths, -1);
			return (NULL);
		}
		if (access(full_path, X_OK) == 0)
		{
			ft_freearr(paths, ft_arrsize(paths));
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_freearr(paths, ft_arrsize(paths));
	return (NULL);
}

char	*resolve_path(const char *cmd_name, t_env *env)
{
	char	**paths;
	char	*path_env;

	if (!cmd_name || !env)
		return (NULL);
	if (ft_strchr(cmd_name, '/'))
		return (check_direct_path(cmd_name));
	path_env = env_getvalue(env, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	return (search_in_path(paths, cmd_name));
}
