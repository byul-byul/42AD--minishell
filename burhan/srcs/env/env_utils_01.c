/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:16:45 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/25 09:21:32 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_wrapper.h"

static void	free_envvar(t_env_var *envvar)
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

int	env_remove_envvar(t_env *env, const char *key)
{
	t_env_var	*curr;
	t_env_var	*prev;

	if (!env || !key)
		return (0);
	curr = env->var_list;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				env->var_list = curr->next;
			free_envvar(curr);
			env->size--;
			env->is_actual = 0;
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
