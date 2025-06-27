/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:29:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/27 02:53:07 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "exec.h"
# include "utils.h"

typedef struct s_minishell
{
	t_env		*env;
	t_token		*token_list;
	t_ast_node	*ast;
}				t_minishell;

int		run_minishell(char **envp);
void	print_message_by_code(int msg_code, char *msg_part);
void	clean_shell(t_minishell *sh, int clean_env);

#endif
