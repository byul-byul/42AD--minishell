/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 04:29:13 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 10:36:19 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

void	print_parser_result(t_ast_node *ast)
{
	ft_printf(C_BLUE "parser() returned AST:\n" C_RESET);
	print_ast_tree(ast, 0);
}
