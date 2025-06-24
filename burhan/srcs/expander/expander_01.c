/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:20:23 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/23 21:03:48 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_wrapper.h"

static int	append_env_var(char **str, const char *value, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*var_name;
	char	*env_value;
	int		res;

	len = 0;
	start = *i + 1;
	if (!*str || !value)
		return (0);
	while (ft_isalnum(value[start + len]) || value[start + len] == '_')
		len++;
	var_name = ft_substr(value, start, len);
	if (!var_name)
		return (0);
	env_value = getenv(var_name);
	if (env_value)
		res = ft_safeappendstr(str, env_value);
	else
		res = ft_safeappendstr(str, "");
	free(var_name);
	*i = start + len;
	return (res);
}

static int	expand_dollar_sign(char **result, const char *value,
								size_t *i, int last_exit_status)
{
	char	*exit_str;
	int		res;

	if (value[*i + 1] == '?')
	{
		*i += 2;
		exit_str = ft_itoa(last_exit_status);
		if (!exit_str)
			return (0);
		res = ft_safeappendstr(result, exit_str);
		free(exit_str);
		return (res);
	}
	else if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
		return (append_env_var(result, value, i));
	if (!ft_safeappendchar(result, '$'))
		return (0);
	return ((*i)++, 1);
}

static int	is_escaped(const char *str, size_t i)
{
	int	count;

	count = 0;
	if (i == 0)
		return (0);
	while (i-- > 0 && str[i] == '\\')
		count++;
	return (count % 2 == 1);
}

static int	handle_escape(char **res, const char *val,
						const char *qmap, size_t *i)
{
	if (val[*i] == '\\' && qmap[*i] != '1')
	{
		(*i)++;
		if (val[*i])
		{
			if (!ft_safeappendchar(res, val[*i]))
				return (0);
			(*i)++;
		}
		return (1);
	}
	return (0);
}

char	*expand_token_value(const char *val, const char *qmap, int status)
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
		if (ft_isdollarsign(val[i]) && val[i + 1] && qmap[i] != '1'
			&& !is_escaped(val, i))
		{
			if (!expand_dollar_sign(&res, val, &i, status))
				return (free(res), NULL);
		}
		else if (!handle_escape(&res, val, qmap, &i)
			&& (!ft_safeappendchar(&res, val[i++])))
			return (free(res), NULL);
	}
	return (res);
}
