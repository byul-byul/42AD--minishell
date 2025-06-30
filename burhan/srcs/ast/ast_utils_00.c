/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils_00.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:35:44 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 13:32:54 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_wrapper.h"

void	free_command(t_command *cmd)
{
	int		i;
	t_redir	*redir;
	t_redir	*tmp;

	if (!cmd)
		return ;
	i = -1;
	if (cmd->argv)
	{
		while (cmd->argv[++i])
			free(cmd->argv[i]);
		free(cmd->argv);
	}
	redir = cmd->redirections;
	while (redir)
	{
		tmp = redir->next;
		free(redir->filename);
		free(redir);
		redir = tmp;
	}
	free(cmd);
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_COMMAND && node->command)
		free_command(node->command);
	free(node);
}

static void	print_ast_node_type(t_ast_node *node)
{
	int	i;

	i = 0;
	if (node->type == NODE_COMMAND)
	{
		ft_printf(C_RED "COMMAND:" C_RESET " ");
		while (node->command->argv && node->command->argv[i])
		{
			ft_printf("%s", node->command->argv[i]);
			if (node->command->argv[i + 1])
				ft_putchar(' ');
			i++;
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

void	print_ast_tree(t_ast_node *node, int depth)
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

t_ast_node	*create_ast_node(t_node_type type, t_ast_node *left,
				t_ast_node *right)
{
	t_ast_node	*node;

	node = ft_calloc(1, sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->command = NULL;
	return (node);
}
