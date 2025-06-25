/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_02.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 18:16:45 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/25 09:22:32 by bhajili          ###   ########.fr       */
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
