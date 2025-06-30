/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:30:55 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/01 01:19:48 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

void	print_parser_result(t_ast_node *ast)
{
	ft_printf(C_BLUE "parser() returned AST:\n" C_RESET);
	print_ast_tree(ast, 0);
}

void	print_parser_error(const char *msg, const char *token_value)
{
	if (token_value)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(token_value, 2);
		ft_putstr_fd("'\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
}
