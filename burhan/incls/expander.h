/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 10:21:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 14:43:54 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "lexer.h"

void	expander(t_token *token_list, int exit_status);
char	*expand_token_value(const char *value, const char *quote_map,
			int last_exit_status);
#endif