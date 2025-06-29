/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:21:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 09:24:06 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"
# include "env.h"

t_token	*expander(t_token *token_list, t_env *env);
char	*expand_token_value(const char *val, const char *qmap, t_env *env);

void	print_expander_result(t_token *token_list);

#endif