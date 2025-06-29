/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:20:23 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 09:24:46 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_wrapper.h"

static int	append_env_var(char **str, const char *value, size_t *i, t_env *env)
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
	env_value = env_getvalue(env, var_name);
	if (env_value)
		res = ft_safeappendstr(str, env_value);
	else
		res = ft_safeappendstr(str, "");
	free(var_name);
	*i = start + len;
	return (res);
}

static int	expand_dollar_sign(char **result, const char *value,
								size_t *i, t_env *env)
{
	char	*exit_str;
	int		res;

	if (value[*i + 1] == '?')
	{
		*i += 2;
		exit_str = ft_itoa(env->last_status);
		if (!exit_str)
			return (0);
		res = ft_safeappendstr(result, exit_str);
		free(exit_str);
		return (res);
	}
	else if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
		return (append_env_var(result, value, i, env));
	if (!ft_safeappendchar(result, '$'))
		return (0);
	return ((*i)++, 1);
}

// static int	is_escaped(const char *str, size_t i)
// {
// 	int	count;

// 	count = 0;
// 	if (i == 0)
// 		return (0);
// 	while (i-- > 0 && str[i] == '\\')
// 		count++;
// 	return (count % 2 == 1);
// }

// static int	handle_escape(char **res, const char *val,
// 						const char *qmap, size_t *i)
// {
// 	if (!res || !val || !qmap || !i)
// 		return (0);
// 	if (val[*i] == '\\' && qmap[*i] != '1')
// 	{
// 		(*i)++;
// 		if (val[*i])
// 		{
// 			if (!ft_safeappendchar(res, val[*i]))
// 				return (0);
// 			(*i)++;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

char	*expand_token_value(const char *val, const char *qmap, t_env *env)
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

// static int	handle_dollar_exit(char **res, size_t *i, int status)
// {
// 	char	*str;

// 	str = ft_itoa(status);
// 	if (!str)
// 		return (0);
// 	*i += 2;
// 	if (!ft_safeappendstr(res, str))
// 		return (free(str), 0);
// 	free(str);
// 	return (1);
// }

// static int	handle_dollar_env(char **res, const char *val,
// 								size_t *i, t_env *env)
// {
// 	size_t	start;
// 	size_t	len;
// 	char	*var_name;
// 	char	*env_value;
// 	int		result;

// 	start = *i + 1;
// 	len = 0;
// 	while (ft_isalnum(val[start + len]) || val[start + len] == '_')
// 		len++;
// 	var_name = ft_substr(val, start, len);
// 	if (!var_name)
// 		return (0);
// 	env_value = env_getvalue(env, var_name);
// 	if (env_value)
// 		result = ft_safeappendstr(res, env_value);
// 	else
// 		result = ft_safeappendstr(res, "");
// 	free(var_name);
// 	*i = start + len;
// 	return (result);
// }

// static int	is_escaped(const char *str, size_t i)
// {
// 	int	count;

// 	count = 0;
// 	if (i == 0)
// 		return (0);
// 	while (i-- > 0 && str[i] == '\\')
// 		count++;
// 	return (count % 2 == 1);
// }

// static int	handle_escape(char **res, const char *val,
// 						const char *qmap, size_t *i)
// {
// 	if (val[*i] == '\\' && qmap[*i] != '1')
// 	{
// 		(*i)++;
// 		if (val[*i])
// 		{
// 			if (!ft_safeappendchar(res, val[*i]))
// 				return (0);
// 			(*i)++;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// char	*expand_token_value(const char *val, const char *qmap,
// 			int status, t_env *env)
// {
// 	char	*res;
// 	size_t	i;

// 	if (!val || !qmap)
// 		return (NULL);
// 	res = ft_strdup("");
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (val[i])
// 	{
// 		if (ft_isdollarsign(val[i]) && val[i + 1] && qmap[i] != '1'
// 			&& !is_escaped(val, i))
// 		{
// 			if (val[i + 1] == '?')
// 			{
// 				if (!handle_dollar_exit(&res, &i, status))
// 					return (free(res), NULL);
// 			}
// 			else if (ft_isalpha(val[i + 1]) || val[i + 1] == '_')
// 			{
// 				if (!handle_dollar_env(&res, val, &i, env))
// 					return (free(res), NULL);
// 			}
// 			else
// 			{
// 				if (!ft_safeappendchar(&res, '$'))
// 					return (free(res), NULL);
// 				i++;
// 			}
// 		}
// 		else if (!handle_escape(&res, val, qmap, &i)
// 			&& (!ft_safeappendchar(&res, val[i++])))
// 			return (free(res), NULL);
// 	}
// 	return (res);
// }
