/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_01.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:16:45 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/22 23:01:22 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_wrapper.h"

static int	update_envvar_value(t_env_var *envvar, const char *new_value)
{
	free(envvar->value);
	envvar->value = ft_strdup(new_value);
	return (envvar->value != NULL);
}

int	env_set(t_env *env, const char *key, const char *value)
{
	t_env_var	*curr;

	if (!env || !key)
		return (0);
	env->is_actual = 0;
	curr = env->var_list;
	while (curr)
	{
		ft_strcmp(curr->key, key);
		if (ft_strcmp(curr->key, key) == 0)
			return (update_envvar_value(curr, value));
		curr = curr->next;
	}
	curr = malloc(sizeof(t_env_var));
	if (!curr)
		return (0);
	curr->key = ft_strdup(key);
	if (!curr->key)
		return (free(curr), 0);
	curr->value = ft_strdup(value);
	if (!curr->value)
		return (free(curr->key), free(curr), 0);
	curr->next = env->var_list; // ADDING TO THE START! IS THIS OK ???
	env->var_list = curr;
	env->size++;
	return (1);
}

static char	*concatenate_envvar_keyvalue(t_env_var *envvar)
{
	char	*keyval[2];

	if (!envvar)
		return (NULL);
	keyval[0] = envvar->key;
	keyval[1] = envvar->value;
	return (ft_strjoin_charset(2, (const char **)keyval, "="));
}

char	**env_to_envp_array(t_env *env)
{
	t_env_var	*curr;
	char		**envp;
	size_t		i;

	if (!env || !env->var_list)
		return (NULL);
	if (env->is_actual == 1)
		return (env->envp);
	envp = malloc(sizeof(char *) * (env->size + 1));
	if (!envp)
		return (NULL);
	curr = env->var_list;
	i = -1;
	while (curr)
	{
		envp[++i] = concatenate_envvar_keyvalue(curr);
		if (!envp[i])
			return (ft_freearr(envp, i), NULL);
		curr = curr->next;
	}
	envp[i] = NULL;
	free(env->envp);
	env->envp = envp;
	env->is_actual = 1;
	return (envp);
}

void	env_print(t_env *env)
{
	t_env_var	*curr;

	if (!env || !env->var_list)
		return ;
	curr = env->var_list;
	while (curr)
	{
		if (curr->value)
			ft_printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
}
