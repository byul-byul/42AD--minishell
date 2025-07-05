/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:21:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 06:50:54 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include <dirent.h>
# include <fnmatch.h>

# include "lexer.h"
# include "env.h"
# include "signals.h"

# define DOLLAR_SIGN	'$'
# define WILDCARD_SIGN	'*'

t_token	*expander(t_token *token_list, t_env *env);
int		handle_dollar_expansion(t_token *token, t_env *env);
int		expand_dollar_sign(char **res, const char *val, size_t *i, t_env *env);
int		handle_wildcard_expansion(t_token **head, t_token *curr);

void	print_expander_result(t_token *token_list);

#endif