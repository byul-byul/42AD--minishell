/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_02.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 01:34:54 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/04 20:33:19 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

int	is_valid_key(const char *key)
{
	if (!key || !ft_isalpha(*key))
		return (0);
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (0);
		key++;
	}
	return (1);
}

static int	is_numeric(const char *str)
{
	if (!str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	run_exit(t_command *cmd)
{
	ft_putendl_fd("exit", 2);
	if (!cmd->argv[1])
		return (EXIT_CODE_SIGNALLED);
	if (!is_numeric(cmd->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(cmd->argv[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		return (EXIT_CODE_SIGNALLED);
	}
	if (cmd->argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (EXIT_CODE_SIGNALLED);
	}
	return (EXIT_CODE_SIGNALLED);
}

int	run_env(t_env *env)
{
	t_env_var	*var;

	if (!env)
		return (1);
	var = env->var_list;
	while (var)
	{
		if (var->value)
			ft_printf("%s=%s\n", var->key, var->value);
		var = var->next;
	}
	return (0);
}

int	run_unset(t_command *cmd, t_env *env)
{
	int		i;

	if (!cmd || !env || !cmd->argv[1])
		return (0);
	i = 1;
	while (cmd->argv[i])
	{
		if (is_valid_key(cmd->argv[i]))
			env_varlist_remove(env, cmd->argv[i]);
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd->argv[i], 2);
			ft_putendl_fd("': not a valid identifier", 2);
		}
		i++;
	}
	return (0);
}
