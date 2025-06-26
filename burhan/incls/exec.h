/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 01:07:25 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/26 12:50:46 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>

# include "env.h"
# include "parser.h"
# include "signals.h"

typedef enum e_status_code
{
	DEFAULT_STATUS,
	REDIR_STATUS
}				t_status_code;

extern int	g_exit_status;

int		exec_ast(t_ast_node *node, t_env *env);
int		exec_command(t_command *cmd, t_env *env);

void	print_error(int error_code);

#endif