/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:20:23 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/30 17:45:00 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander_wrapper.h"

void	print_expander_result(t_token *token_list)
{
	ft_printf(C_BLUE "expander() returned:\n" C_RESET);
	print_token_list(token_list);
}

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

t_token	*expander(t_token *token_list, t_env *env)
{
	char			*tmp;
	char			*expanded;
	t_token			*head;

	head = token_list;
	while (token_list)
	{
		if (token_list->type == WORD && token_list->value
			&& token_list->quote_map)
		{
			tmp = token_list->value;
			expanded = expand_token_value(token_list->value,
					token_list->quote_map, env);
			if (!expanded)
				return (free(tmp), NULL);
			if (ft_strcmp(tmp, expanded))
				token_list->expanded = 1;
			token_list->value = expanded;
			free(tmp);
			token_list->type = get_token_type(token_list->value,
					token_list->quote_map);
		}
		token_list = token_list->next;
	}
	return (head);
}
