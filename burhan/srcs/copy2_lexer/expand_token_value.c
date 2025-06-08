/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/31 13:45:34 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static void	append_exit_status(char **result, int last_exit_status)
{
	char	*tmp;
	char	*exit_str;

	exit_str = ft_itoa(last_exit_status);
	if (!exit_str)
		return ;
	tmp = *result;
	*result = ft_strjoin(*result, exit_str);
	free(tmp);
	free(exit_str);
}

static void	append_env_var(char **result, const char *value, size_t *i)
{
	size_t	start;
	size_t	len;
	char	*var_name;
	char	*env_value;
	char	*tmp;

	start = *i + 1;
	len = 0;
	while (ft_isalnum(value[start + len]) || value[start + len] == '_')
		len++;
	var_name = ft_substr(value, start, len);
	env_value = getenv(var_name);
	tmp = *result;
	*result = ft_strjoin(*result, env_value ? env_value : "");
	free(tmp);
	free(var_name);
	*i = start + len;
}

static int	handle_dollar_case(char **result, const char *value,
								size_t *i, int last_exit_status)
{
	if (value[*i + 1] == '?')
	{
		append_exit_status(result, last_exit_status);
		*i += 2;
	}
	else if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
		append_env_var(result, value, i);
	else
	{
		result = safe_append_char(result, '$');
		if (!result)
				return (NULL);
		(*i)++;
	}
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
		if (value[i] == '$' && value[i + 1])
		{
			if (!handle_dollar_case(&result, value, &i, last_exit_status))
				return (free(result), NULL);
		}
		else
		{
			result = safe_append_char(result, value[i]);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}
