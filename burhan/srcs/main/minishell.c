/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:35:16 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/26 13:00:44 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_wrapper.h"

static int	exit_minishell(t_minishell *sh, int msg_code)
{
	clean_shell(sh, TRUE);
	print_message_by_code(msg_code, NULL);
	return (msg_code);
}

static char	*read_input(void)
{
	char	*line;

	print_message_by_code(MSH_CODE_PROMPT, NULL);
	line = readline("");
	if (line && *line)
		add_history(line);
	return (line);
}

static int	init_minishell(t_minishell *sh, char **envp)
{
	if (!sh)
		return (ERR_CODE_ENV_INIT);
	sh->ast = NULL;
	sh->token_list = NULL;
	sh->env = env_init(envp);
	if (!sh->env)
		return (ERR_CODE_ENV_INIT);
	return (0);
}

static int	handle_input(t_minishell *sh, char *line, int prev_exit_code)
{
	sh->token_list = expander(lexer(line), prev_exit_code);
	if (!sh->token_list)
		return (ERR_CODE_MALLOC);
	sh->ast = parser(sh->token_list);
	if (!sh->ast)
		return (ERR_CODE_MALLOC);
	return (exec_ast(sh->ast, sh->env));
}

int	minishell(char **envp)
{
	char		*line;
	int			status;
	t_minishell	sh;
	
	status = init_minishell(&sh, envp);
	if (status)
		return (exit_minishell(&sh, status));
	while (TRUE)
	{
		line = read_input();
		if (!line)
			return (exit_minishell(&sh, ERR_CODE_READLINE_FAILED));
		status = handle_input(&sh, line, status);
		free(line);
		clean_shell(&sh, FALSE);
		if (EXIT_CODE_SIGNALLED == status)
			return (exit_minishell(&sh, MSH_CODE_EXIT_EOF));
	}
}
