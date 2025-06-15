/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:20:23 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/15 12:31:06 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_wrapper.h"

static t_token_type	get_token_type(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len == 1 && str[0] == '|')
		return (PIPE);
	if (len == 1 && str[0] == '<')
		return (REDIR_IN);
	if (len == 1 && str[0] == '>')
		return (REDIR_OUT);
	if (len == 1 && str[0] == '(')
		return (OPEN_PAREN);
	if (len == 1 && str[0] == ')')
		return (CLOSE_PAREN);
	if (len == 2 && str[0] == '<' && str[1] == '<')
		return (HEREDOC);
	if (len == 2 && str[0] == '>' && str[1] == '>')
		return (APPEND);
	if (len == 2 && str[0] == '&' && str[1] == '&')
		return (LOGICAL_AND);
	if (len == 2 && str[0] == '|' && str[1] == '|')
		return (LOGICAL_OR);
	return (WORD);
}

static int	append_exit_status(char **str, int last_exit_status)
{
	char	*exit_str;
	int		res;

	if (!*str)
		return (0);
	exit_str = ft_itoa(last_exit_status);
	if (!exit_str)
		return (0);
	res = ft_safeappendstr(str, exit_str);
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
	if (value[*i + 1] == '?')
		return (*i += 2, append_exit_status(result, last_exit_status));
	else if (ft_isalpha(value[*i + 1]) || value[*i + 1] == '_')
		return (append_env_var(result, value, i));
	if (!ft_safeappendchar(result, '$'))
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
		if (ft_isdollarsign(value[i]) && value[i + 1])
		{
			if (!expand_dollar_sign(&result, value, &i, last_exit_status))
				return (free(result), NULL);
		}
		else
		{
			if (!ft_safeappendchar(&result, value[i]))
				return (free(result), NULL);
			i++;
		}
	}
	return (result);
}

void	expander(t_token *token_list, int exit_status)
{
	char	*tmp;
	char	*expanded;

	while (token_list)
	{
		if (token_list->type == WORD)
		{
			tmp = token_list->value;
			expanded = expand_token_value(token_list->value,
					token_list->quoted, exit_status);
			token_list->expanded = (expanded && ft_strcmp(tmp, expanded) != 0);
			token_list->value = expanded;
			free(tmp);
			token_list->type = get_token_type(token_list->value);
		}
		token_list = token_list->next;
	}
}
