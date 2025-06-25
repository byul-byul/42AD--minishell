/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:16:45 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/25 09:32:18 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_wrapper.h"

static t_env_var	*envvar_init(char *keyvalue)
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
		return (free(envvar), NULL);
	return (envvar);
}

static int	add_to_varlist(t_env_var **head, t_env_var *envvar)
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

static t_env_var	*varlist_init(char **envp)
{
	t_env_var	*var_list;
	size_t		size;
	size_t		i;
	int			res;

	if (!envp || !*envp)
		return (NULL);
	i = 0;
	size = ft_arrsize(envp);
	var_list = NULL;
	while (i < size)
	{
		res = add_to_varlist(&var_list, envvar_init(envp[i]));
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
	env->var_list = NULL;
	env->envp = NULL;
	env->size = 0;
	env->envp = ft_arrdup(envp, ft_arrsize(envp));
	if (!env->envp)
		return (env_free(env), NULL);
	env->var_list = varlist_init(env->envp);
	if (!env->var_list)
		return (env_free(env), NULL);
	env->is_actual = 1;
	return (env);
}

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
