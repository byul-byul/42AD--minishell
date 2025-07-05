/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_03.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:35:51 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 20:36:27 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

static int	print_cd_error(const char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd((char *)path, 2);
	perror(" ");
	return (1);
}

static void	update_pwd_vars(t_env *env, char *oldpwd)
{
	char	cwd[PATH_MAX];

	if (oldpwd)
	{
		env_setvalue(env, "OLDPWD", oldpwd);
		free(oldpwd);
	}
	if (getcwd(cwd, sizeof(cwd)))
		env_setvalue(env, "PWD", cwd);
}

int	run_cd(t_command *cmd, t_env *env)
{
	const char	*path;
	char		*home;
	char		*oldpwd;

	if (!cmd || !env)
		return (1);
	path = cmd->argv[1];
	if (!path)
	{
		home = env_getvalue(env, "HOME");
		if (!home)
			return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
		path = home;
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
		return (free(oldpwd), print_cd_error(path));
	update_pwd_vars(env, oldpwd);
	return (0);
}
