/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:16:45 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/23 00:02:02 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_wrapper.h"

t_env	*env_init(char **envp)
{
	t_env	*env;
	size_t	size;
	char	**keyvalue;

	if (!envp || !*envp)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->var_list = NULL;
	env->size = 0;
	size = ft_arrsize(envp);
	env->envp = ft_arrdup(envp, size);
	if (!env->envp)
		return (free(env), NULL);
	while (size--)
	{
		keyvalue = ft_split_charset(env->envp[size], "=");
		if (!keyvalue)
			return (free(env), NULL);
		env_set(env, keyvalue[0], keyvalue[1]);
		free(keyvalue);
	}
	env->is_actual = 1;
	return (env);
}

static void	free_var_list(t_env_var *head)
{
	t_env_var	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free(head->key);
		free(head->value);
		free(head);
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
		free_var_list(env->var_list);
	free(env);
}

char	*env_get(t_env *env, const char *key)
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

int	env_unset(t_env *env, const char *key)
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
			free(curr->key);
			free(curr->value);
			free(curr);
			return (env->size--, env->is_actual = 0, 1);
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}
