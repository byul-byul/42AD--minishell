/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:07:25 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/18 01:20:45 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../incls/parser.h"
# include <sys/types.h>
// # include <sys/wait.h>


// === Entry point ===
// Executes the given AST
int		exec_ast(t_ast_node *node);

// === Command execution ===
// Executes a simple command (external or builtin)
int		exec_command(t_command *cmd);
int		exec_builtin(char **argv);
int		exec_forked_command(t_ast_node *node);

// === Redirection handling ===
// Sets up input/output redirections from the list
int		handle_redirections(t_redir *redir_list);
int		setup_heredocs(t_redir *redir_list);

// === Builtin utilities ===
// Returns 1 if the given command is a builtin
int		is_builtin(char *cmd);
// Executes a builtin command (already detected)
int		exec_builtin(char **argv);

// === Logical operators and control flow ===
// Executes a pipe: left | right
int		exec_pipe(t_ast_node *left, t_ast_node *right);
// Executes a logical AND: left && right
int		exec_and(t_ast_node *left, t_ast_node *right);
// Executes a logical OR: left || right
int		exec_or(t_ast_node *left, t_ast_node *right);
// Executes a subshell (grouped command in parentheses)
int		exec_subshell(t_ast_node *subtree);

// === Signal handling ===
void	setup_signals(int is_child);

// === Wildcard expansion (bonus) ===
char	**expand_wildcards(char **argv);

// === Global exit status ===
// Updated after each command
extern int	g_exit_status;

#endif
