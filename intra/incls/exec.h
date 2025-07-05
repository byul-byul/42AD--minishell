/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqaroot <oqaroot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:07:25 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/04 17:38:34 by oqaroot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>

# include "parser.h"

typedef enum e_status_code
{
	DEFAULT_STATUS,
	REDIR_STATUS
}				t_status_code;

int		exec_ast(t_ast_node *node, t_env *env);
int		exec_command(t_command *cmd, t_env *env);
int		exec_external(t_command *cmd, t_env *env);
char	*resolve_path(const char *cmd_name, t_env *env);

int		is_builtin(char *cmd);
int		exec_builtin(t_command *cmd, t_env *env);
int		run_export(t_command *cmd, t_env *env);
int		run_unset(t_command *cmd, t_env *env);
int		run_env(t_env *env);
int		run_exit(t_command *cmd);
int		is_valid_key(const char *key);
int		handle_heredocs(t_command *cmd);
int		exec_pipe(t_ast_node *left, t_ast_node *right, t_env *env);
int		handle_and_return_status(int status);
int		run_cd(t_command *cmd, t_env *env);
#endif