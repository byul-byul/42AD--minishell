/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:26:42 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/01 02:48:29 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "ast.h"
# include "expander.h"
# include "utils.h"

t_ast_node	*parser(t_token *token_list);
t_ast_node	*parse_command(t_token **token_list);
t_ast_node	*parse_subshell(t_token **token_list);
int			parse_args_and_redirs(t_token **tl, t_list **argv, t_command *cmd);
void		print_parser_error(int msg_code, const char *msg_part);
void		print_parser_result(t_ast_node *ast);

#endif