/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 01:34:54 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 01:25:24 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

static int	handle_export_arg(char *arg, t_env *env)
{
	char		*sep;
	char		*key;

	sep = ft_strchr(arg, '=');
	if (!sep)
		key = ft_strdup(arg);
	else
		key = ft_strndup(arg, sep - arg);
	if (!is_valid_key(key))
	{
		ft_putendl_fd("minishell: export: not a valid identifier", 2);
		return (free(key), 1);
	}
	if (!env_varlist_add(env, env_varinit(arg)))
		return (free(key), 1);
	return (free(key), 0);
}

int	run_export(t_command *cmd, t_env *env)
{
	int	i;

	if (!cmd || !env)
		return (1);
	if (!cmd->argv[1])
	{
		env_print(env, TRUE);
		return (0);
	}
	i = 1;
	while (cmd->argv[i])
	{
		if (handle_export_arg(cmd->argv[i], env))
			return (1);
		i++;
	}
	return (0);
}
