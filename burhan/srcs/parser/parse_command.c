/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 22:56:39 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 19:36:42 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_wrapper.h"

static char	**list_to_str_array(t_list *list)
{
	int		size;
	char	**array;
	int		i;

	size = ft_lstsize(list);
	array = ft_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (list)
	{
		array[i++] = ft_strdup((char *)list->content);
		list = list->next;
	}
	array[i] = NULL;
	return (array);
}

static int	finalize_command(t_command *cmd, t_list *argv_list)
{
	cmd->argv = list_to_str_array(argv_list);
	ft_lstclear(&argv_list, free);
	if (!cmd->argv)
	{
		free_command(cmd);
		return (1);
	}
	if (!cmd->argv[0] && !cmd->redirections)
	{
		free_command(cmd);
		return (1);
	}
	return (0);
}

static t_command	*parse_simple_command(t_token **token_list)
{
	t_command	*cmd;
	t_list		*argv_list;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->redirections = NULL;
	argv_list = NULL;
	if (parse_args_and_redirs(token_list, &argv_list, cmd))
	{
		free_command(cmd);
		ft_lstclear(&argv_list, free);
		return (NULL);
	}
	if (finalize_command(cmd, argv_list))
		return (NULL);
	return (cmd);
}

t_ast_node	*parse_command(t_token **token_list)
{
	t_command	*cmd;
	t_ast_node	*node;

	if (*token_list && (*token_list)->type == OPEN_PAREN)
		return (parse_subshell(token_list));
	cmd = parse_simple_command(token_list);
	if (!cmd)
		return (NULL);
	node = create_ast_node(NODE_COMMAND, NULL, NULL);
	node->command = cmd;
	return (node);
}
