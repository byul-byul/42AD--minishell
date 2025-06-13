/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/13 18:07:45 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static int	append_exit_status(char **str, int last_exit_status)
{
	char	*exit_str;
	int		res;

	if (!*str)
		return (0);
	exit_str = ft_itoa(last_exit_status);
	if (!exit_str)
		return (0);
	res = safe_append_str(str, exit_str);
	free(exit_str);
	return (res);
}

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
		res = safe_append_str(str, env_value);
	else
		res = safe_append_str(str, "");
	free(var_name);
	*i = start + len;
	return (res);
}

// static int	expand_dollar_sign(char **result, const char *value,
// 								size_t *i, int last_exit_status)
// {
// 	if (value[*i + 1] == '?')
// 		return (*i += 2, append_exit_status(result, last_exit_status));
// 	else if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
// 		return (append_env_var(result, value, i));
// 	return ((*i)++, 1);
// }

static int	expand_dollar_sign(char **result, const char *value,
								size_t *i, int last_exit_status)
{
	if (value[*i + 1] == '?')
		return (*i += 2, append_exit_status(result, last_exit_status));
	else if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
		return (append_env_var(result, value, i));
	if (!safe_append_char(result, '$'))
		return (0);
	return ((*i)++, 1);
}

char	*expand_token_value(const char *value, t_quote_type quoted,
						int last_exit_status)
{
	char	*result;
	size_t	i;

	if (quoted == SINGLE)
		return (ft_strdup(value));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (is_dollar_sign(value[i]) && value[i + 1])
		{
			if (!expand_dollar_sign(&result, value, &i, last_exit_status))
				return (free(result), NULL);
		}
		else
		{
			if (!safe_append_char(&result, value[i]))
				return (free(result), NULL);
			i++;
		}
	}
	return (result);
}
