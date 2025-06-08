/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:26:42 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/28 17:54:11 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "lexer.h"

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
	int				type;     // REDIR_IN, REDIR_OUT, APPEND, HEREDOC
	char			*filename;
	int				heredoc_expand; // 1 — если нужно развернуть $
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
	t_command			*command;  // Только если type == NODE_COMMAND
}	t_ast_node;

t_ast_node	*parser(t_token *token_list);
void		free_ast(t_ast_node *node);
void		parser_error(const char *msg, const char *token_value);
t_ast_node	*create_ast_node(t_node_type type, t_ast_node *left, t_ast_node *right);
void		free_command(t_command *cmd);
t_ast_node	*parse_logical_or(t_token **token_list);

#endif