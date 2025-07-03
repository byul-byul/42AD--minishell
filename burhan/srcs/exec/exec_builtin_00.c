/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 01:34:54 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 06:55:07 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

static int	run_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putendl(cwd);
	return (0);
}

static int	run_cd(t_command *cmd, t_env *env)
{
	const char	*path;
	char		*home;

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
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd((char *)path, 2);
		perror(" ");
		return (1);
	}
	return (0);
}

static int	run_echo(t_command *cmd)
{
	int		i;
	int		newline;

	i = 1;
	newline = 1;
	if (cmd->argv[i] && !ft_strcmp(cmd->argv[i], "-n"))
	{
		newline = 0;
		i++;
	}
	while (cmd->argv[i])
	{
		ft_putstr(cmd->argv[i]);
		if (cmd->argv[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (newline)
		ft_putchar('\n');
	return (0);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	return (!ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd")
		|| !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

int	exec_builtin(t_command *cmd, t_env *env)
{
	char	*name;
	int		res;

	res = 1;
	if (!cmd || !cmd->argv || !cmd->argv[0])
		return (res);
	name = cmd->argv[0];
	if (!ft_strcmp(name, "echo"))
		res = run_echo(cmd);
	else if (!ft_strcmp(name, "cd"))
		res = run_cd(cmd, env);
	else if (!ft_strcmp(name, "pwd"))
		res = run_pwd();
	else if (!ft_strcmp(name, "export"))
		res = run_export(cmd, env);
	else if (!ft_strcmp(name, "unset"))
		res = run_unset(cmd, env);
	else if (!ft_strcmp(name, "env"))
		res = run_env(env);
	else if (!ft_strcmp(name, "exit"))
		res = run_exit(cmd);
	return (res);
}
