/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:16:45 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 00:58:18 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_wrapper.h"

char	*env_getvalue(t_env *env, const char *key)
{
	t_env_var	*curr;

	if (!env || !key)
		return (NULL);
	curr = env->var_list;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

int	env_varlist_pop(t_env_var **head, const char *key)
{
	t_env_var	*curr;
	t_env_var	*prev;

	if (!head || !key)
		return (0);
	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*head = curr->next;
			free_envvar(curr);
			return (1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

int	env_varlist_remove(t_env *env, const char *key)
{
	int	res;

	res = 0;
	if (!env || !key)
		return (0);
	res = env_varlist_pop(&env->var_list, key);
	if (res)
	{
		env->size--;
		env->is_actual = 0;
	}
	return (res);
}

int	env_varlist_push(t_env_var **head, t_env_var *envvar)
{
	t_env_var	*curr;

	if (!head || !envvar)
		return (0);
	if (!*head)
		*head = envvar;
	else
	{
		curr = *head;
		while (curr->next)
			curr = curr->next;
		curr->next = envvar;
	}
	envvar->next = NULL;
	return (1);
}

int	env_varlist_add(t_env *env, t_env_var *envvar)
{
	int	res;

	res = 0;
	if (!env || !envvar)
		return (0);
	env_varlist_remove(env, envvar->key);
	res = env_varlist_push(&env->var_list, envvar);
	if (res)
	{
		env->is_actual = 0;
		env->size++;
	}
	return (res);
}
