/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:26:42 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 10:45:55 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "expander.h"

t_ast_node	*parser(t_token *token_list);
void		parser_error(const char *msg, const char *token_value);
t_ast_node	*parse_logical_or(t_token **token_list);
void		print_parser_result(t_ast_node *ast);

#endif