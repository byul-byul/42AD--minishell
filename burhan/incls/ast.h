/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 10:29:03 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 16:29:36 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

# include "libft.h"

# define C_RESET   "\033[0m"
# define C_RED     "\033[31m"
# define C_GREEN   "\033[32m"
# define C_YELLOW  "\033[33m"
# define C_MAGENTA "\033[35m"

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_SUBSHELL
}			t_node_type;

typedef struct s_redir
{
	int				fd;
	int				type;
	char			*filename;
	int				heredoc_expand;
	struct s_redir	*next;
}	t_redir;

typedef struct s_command
{
	char	**argv;
	t_redir	*redirections;
}	t_command;

typedef struct s_ast_node
{
	t_node_type			type;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_command			*command;
}	t_ast_node;

t_ast_node	*create_ast_node(t_node_type type,
				t_ast_node *left, t_ast_node *right);
void		free_ast(t_ast_node *node);
void		print_ast_tree(t_ast_node *node, int depth);
void		free_command(t_command *cmd);

#endif