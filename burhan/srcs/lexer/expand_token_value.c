/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_token_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:15:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/15 22:31:03 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

static void	append_exit_status(char **result, int last_exit_status)
{
	char	*tmp;
	char	*exit_str;

	exit_str = ft_itoa(last_exit_status);
	tmp = *result;
	*result = ft_strjoin(*result, exit_str);
	free(tmp);
	free(exit_str);
}

static void	append_env_var(char **result, const char *value, size_t *i)
{
	size_t	start;
	char	*var_name;
	char	*env_value;
	char	*tmp;

	start = *i + 1;
	while (ft_isalnum(value[*i + 1]) || value[*i + 1] == '_')
		(*i)++;
	var_name = ft_substr(value, start, *i - start + 1);
	env_value = getenv(var_name);
	tmp = *result;
	if (env_value)
		*result = ft_strjoin(*result, env_value);
	else
		*result = ft_strjoin(*result, "");
	free(tmp);
	free(var_name);
	(*i)++;
}

static void	append_literal(char **result, char c)
{
	char	*tmp;
	char	str[2];

	str[0] = c;
	str[1] = '\0';
	tmp = *result;
	*result = ft_strjoin(*result, str);
	free(tmp);
}

static void	handle_dollar_case(char **result, const char *value,
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
		append_literal(result, '$');
		(*i)++;
	}
}

char	*expand_token_value(const char *value, int last_exit_status)
{
	char	*result;
	size_t	i;

	result = ft_strdup("");
	i = 0;
	while (value[i])
	{
		if (value[i] == '$' && value[i + 1])
			handle_dollar_case(&result, value, &i, last_exit_status);
		else
		{
			append_literal(&result, value[i]);
			i++;
		}
	}
	return (result);
}
