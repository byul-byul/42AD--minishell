/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:21:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 02:40:07 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "env.h"

t_token	*expander(t_token *token_list, t_env *env);
char	*expand_token_value(const char *val, const char *qmap, t_env *env);
int		expand_dollar_sign(char **res, const char *val, size_t *i, t_env *env);
void	print_expander_result(t_token *token_list);

#endif