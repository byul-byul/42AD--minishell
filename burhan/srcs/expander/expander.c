/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:20:23 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/16 22:31:07 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_wrapper.h"

// int	quote_remover(t_token *token)
// {
// 	char	*stripped;
// 	char	*new_map;
// 	size_t	i;

// 	if (!token || !token->value || !token->quote_map)
// 		return ;
// 	stripped = ft_strdup("");
// 	if (!stripped)
// 		return (0);
// 	new_map = ft_strdup("");
// 	if (!new_map)
// 		return (free(stripped), 0);
// 	i = -1;
// 	while (token->value[++i])
// 	{
// 		if (token->quote_map[i] != '1' && token->quote_map[i] != '2')
// 			if (!ft_safeappendchar(&stripped, token->value[i]) ||
// 				!ft_safeappendchar(&new_map, token->quote_map[i]))
// 				return (free(stripped), free(new_map), 0);
// 	}
// 	free(token->value);
// 	free(token->quote_map);
// 	token->value = stripped;
// 	token->quote_map = new_map;
// 	return (1);
// }

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

char	*expand_token_value(const char *value, const char *quote_map,
						int last_exit_status)
{
	char	*result;
	size_t	i;

	if (!value || !quote_map)
		return (NULL);
	result = ft_strdup("");
	if (!result)
		return (NULL);
	i = 0;
	while (value[i])
	{
		if (ft_isdollarsign(value[i]) && value[i + 1] && quote_map[i] != '1')
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
		if (token_list->type == WORD && token_list->value && token_list->quote_map)
		{
			tmp = token_list->value;
			expanded = expand_token_value(token_list->value,
					token_list->quote_map, exit_status);
			if (!expanded)
				return ;
			if (ft_strcmp(tmp, expanded))
				token_list->expanded = 1;
			token_list->value = expanded;
			free(tmp);
			token_list->type = get_token_type(token_list->value);
		}
		token_list = token_list->next;
	}
}
