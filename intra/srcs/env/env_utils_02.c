/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:16:45 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 20:43:12 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_wrapper.h"

void	env_print(t_env *env, int print_empty_var)
{
	t_env_var	*curr;

	if (!env || !env->var_list)
		return ;
	curr = env->var_list;
	while (curr)
	{
		if (curr->value)
			ft_printf("%s=%s\n", curr->key, curr->value);
		else if (print_empty_var)
			ft_printf("%s=\n", curr->key);
		curr = curr->next;
	}
}

void	free_envvar(t_env_var *envvar)
{
	if (envvar)
	{
		if (envvar->key)
			free(envvar->key);
		if (envvar->value)
			free(envvar->value);
		free(envvar);
	}
}

static void	free_varlist(t_env_var *head)
{
	t_env_var	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free_envvar(head);
		head = tmp;
	}
}

void	env_free(t_env *env)
{
	if (!env)
		return ;
	if (env->envp)
		ft_freearr(env->envp, env->size);
	if (env->var_list)
		free_varlist(env->var_list);
	free(env);
}

int	env_setvalue(t_env *env, const char *key, char *value)
{
	char		*keyvalue;
	t_env_var	*envvar;
	int			res;

	if (!key || !value)
		return (0);
	keyvalue = ft_strjoin(key, "=");
	if (!keyvalue)
		return (0);
	if (!ft_safeappendstr(&keyvalue, value))
		return (0);
	envvar = env_varinit(keyvalue);
	free(keyvalue);
	if (!envvar)
		return (0);
	res = env_varlist_add(env, envvar);
	return (res);
}
