/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:16:45 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 01:03:03 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_wrapper.h"

static char	*concatenate_envvar_keyvalue(t_env_var *envvar)
{
	char	*keyval[2];

	if (!envvar)
		return (NULL);
	keyval[0] = envvar->key;
	keyval[1] = envvar->value;
	return (ft_strjoin_charset(2, (const char **)keyval, "="));
}

char	**env_reassemble_envp(t_env *env)
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
	i = 0;
	while (curr)
	{
		envp[i] = concatenate_envvar_keyvalue(curr);
		if (!envp[i])
			return (ft_freearr(envp, i), NULL);
		curr = curr->next;
		i++;
	}
	envp[i] = NULL;
	free(env->envp);
	env->envp = envp;
	return (env->is_actual = 1, envp);
}

t_env_var	*env_varinit(char *keyvalue)
{
	t_env_var	*envvar;
	char		*separator;

	if (!keyvalue)
		return (NULL);
	envvar = malloc(sizeof(t_env_var));
	if (!envvar)
		return (NULL);
	envvar->key = NULL;
	envvar->value = NULL;
	envvar->next = NULL;
	separator = ft_strchr(keyvalue, '=');
	if (separator)
	{
		envvar->key = ft_strndup(keyvalue, separator - keyvalue);
		envvar->value = ft_strdup(separator + 1);
	}
	else
		envvar->key = ft_strdup(keyvalue);
	return (envvar);
}

static t_env_var	*varlist_init(char **envp, size_t size)
{
	t_env_var	*var_list;
	size_t		i;
	int			res;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	var_list = NULL;
	while (i < size)
	{
		res = env_varlist_push(&var_list, env_varinit(envp[i]));
		if (!res)
			return (NULL);
		i++;
	}
	return (var_list);
}

t_env	*env_init(char **envp)
{
	t_env	*env;

	if (!envp || !*envp)
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->last_status = 0;
	env->var_list = NULL;
	env->envp = NULL;
	env->size = ft_arrsize(envp);
	env->envp = ft_arrdup(envp, env->size);
	if (!env->envp)
		return (env_free(env), NULL);
	env->var_list = varlist_init(env->envp, env->size);
	if (!env->var_list)
		return (env_free(env), NULL);
	env->is_actual = 1;
	return (env);
}
