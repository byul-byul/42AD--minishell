/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:34:41 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 03:15:43 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_wrapper.h"

static int	append_env_var(char **str, const char *val, size_t *i, t_env *env)
{
	size_t	start;
	size_t	len;
	char	*var_name;
	char	*env_value;
	int		res;

	len = 0;
	start = *i + 1;
	if (!*str || !val)
		return (0);
	while (ft_isalnum(val[start + len]) || val[start + len] == '_')
		len++;
	var_name = ft_substr(val, start, len);
	if (!var_name)
		return (0);
	env_value = env_getvalue(env, var_name);
	if (env_value)
		res = ft_safeappendstr(str, env_value);
	else
		res = ft_safeappendstr(str, "");
	free(var_name);
	*i = start + len;
	return (res);
}

int	expand_dollar_sign(char **res, const char *val, size_t *i, t_env *env)
{
	char	*exit_str;
	int		result;

	if (val[*i + 1] == '?')
	{
		*i += 2;
		exit_str = ft_itoa(env->last_status);
		if (!exit_str)
			return (0);
		result = ft_safeappendstr(res, exit_str);
		free(exit_str);
		return (result);
	}
	else if (ft_isalpha(val[*i + 1]) || val[*i + 1] == '_')
		return (append_env_var(res, val, i, env));
	if (!ft_safeappendchar(res, '$'))
		return (0);
	return ((*i)++, 1);
}

