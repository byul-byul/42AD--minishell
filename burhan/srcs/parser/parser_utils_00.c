/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:30:55 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/01 02:15:34 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

void	print_parser_result(t_ast_node *ast)
{
	ft_printf(C_BLUE "parser() returned AST:\n" C_RESET);
	print_ast_tree(ast, 0);
}

void	print_parser_error(int msg_code, const char *msg_part)
{
	print_msg_by_code(msg_code, NULL);
	if (msg_part)
	{
		ft_putstr_fd(msg_part, 2);
		ft_putstr_fd("'", 2);
	}
	ft_putstr_fd("\n", 2);
}
