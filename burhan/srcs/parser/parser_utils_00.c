/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:30:55 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/27 04:29:19 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

void	free_command(t_command *cmd)
{
	int	i;
	t_redir	*redir;
	t_redir	*tmp;

	if (!cmd)
		return;
	if (cmd->argv)
	{
		for (i = 0; cmd->argv[i]; i++)
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

t_ast_node	*create_ast_node(t_node_type type, t_ast_node *left, t_ast_node *right)
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

void	parser_error(const char *msg, const char *token_value)
{
	if (token_value)
	{
		write(2, "minishell: ", 11);
		write(2, msg, ft_strlen(msg));
		write(2, " '", 2);
		write(2, token_value, ft_strlen(token_value));
		write(2, "'\n", 2);
	}
	else
	{
		write(2, "minishell: ", 11);
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 1);
	}
}

void	free_ast(t_ast_node *node)
{
	if (!node)
		return;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_COMMAND && node->command)
		free_command(node->command);
	free(node);
}
