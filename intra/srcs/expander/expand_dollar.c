/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 02:34:41 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 07:05:33 by bhajili          ###   ########.fr       */
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
		exit_str = ft_itoa(g_exit_status);
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

static char	*expand_token_value(const char *val, const char *qmap, t_env *env)
{
	char	*res;
	size_t	i;

	if (!val || !qmap)
		return (NULL);
	res = ft_strdup("");
	if (!res)
		return (NULL);
	i = 0;
	while (val[i])
	{
		if (ft_isdollarsign(val[i]) && val[i + 1] && qmap[i] != '1')
		{
			if (!expand_dollar_sign(&res, val, &i, env))
				return (free(res), NULL);
		}
		else if (!ft_safeappendchar(&res, val[i++]))
			return (free(res), NULL);
	}
	return (res);
}

int	handle_dollar_expansion(t_token *token, t_env *env)
{
	char			*tmp;
	char			*expanded;

	tmp = token->value;
	expanded = expand_token_value(token->value, token->quote_map, env);
	if (!expanded)
		return (free(tmp), 0);
	if (ft_strcmp(tmp, expanded))
		token->expanded = 1;
	token->value = expanded;
	token->type = get_token_type(token->value, token->quote_map);
	return (free(tmp), 1);
}
