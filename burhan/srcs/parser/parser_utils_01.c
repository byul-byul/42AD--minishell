/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_01.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 04:29:13 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/27 04:35:29 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

static void	print_ast_node_type(t_ast_node *node)
{
	if (node->type == NODE_COMMAND)
	{
		ft_printf(C_RED "COMMAND:" C_RESET " ");
		for (int i = 0; node->command->argv && node->command->argv[i]; i++)
		{
			ft_printf("%s", node->command->argv[i]);
			if (node->command->argv[i + 1])
				ft_putchar(' ');
		}
	}
	else if (node->type == NODE_PIPE)
		ft_putstr(C_GREEN "PIPE" C_RESET);
	else if (node->type == NODE_AND)
		ft_putstr(C_YELLOW "AND" C_RESET);
	else if (node->type == NODE_OR)
		ft_putstr(C_YELLOW "OR" C_RESET);
	else if (node->type == NODE_SUBSHELL)
		ft_putstr(C_MAGENTA "SUBSHELL" C_RESET);
}

static void	print_ast_tree(t_ast_node *node, int depth)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i++ < depth)
		ft_putstr("  ");
	ft_putstr("└─ ");
	print_ast_node_type(node);
	ft_putchar('\n');
	print_ast_tree(node->left, depth + 1);
	print_ast_tree(node->right, depth + 1);
}

void	print_parser_result(t_ast_node *ast)
{
	ft_printf(C_BLUE "parser() returned AST:\n" C_RESET);
	print_ast_tree(ast, 0);
}
