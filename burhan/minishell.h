/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 08:52:46 by bhajili           #+#    #+#             */
/*   Updated: 2025/03/10 15:05:02 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./libft/libft.h"

# define PIPE			1
# define REDIR_IN		2
# define REDIR_OUT		3
# define HEREDOC		4
# define APPEND			5
# define LOGICAL_AND	6
# define LOGICAL_OR		7

typedef struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
}				t_token;

typedef struct s_cmd
{
	char			**args;
	int				fd_in;
	int				fd_out;
	int				is_pipe;
	int				is_logical;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_shell
{
	t_env	*env;
	int		last_exit;
	int		stdin_backup;
	int		stdout_backup;
	int		is_interactive;
}				t_shell;

void	minishell(void);
t_token	*lexer(const char *input);
void	free_tokens(t_token *tokens);

#endif
