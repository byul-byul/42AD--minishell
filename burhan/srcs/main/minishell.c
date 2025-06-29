/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:35:16 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 10:26:18 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_wrapper.h"

static int	handle_input(t_minishell *sh, char *line)
{
	sh->token_list = lexer(line);
	if (PROGRAM_MODE == DEBUG_MODE)
		print_lexer_result(line, sh->token_list);
	sh->token_list = expander(sh->token_list, sh->env);
	if (PROGRAM_MODE == DEBUG_MODE)
		print_expander_result(sh->token_list);
	if (!sh->token_list)
		return (ERR_CODE_MALLOC);
	sh->ast = parser(sh->token_list);
	if (PROGRAM_MODE == DEBUG_MODE)
		print_parser_result(sh->ast);
	if (!sh->ast)
		return (ERR_CODE_MALLOC);
	return (exec_ast(sh->ast, sh->env));
}

static int	exit_minishell(t_minishell *sh, int msg_code)
{
	clean_shell(sh, TRUE);
	print_message_by_code(msg_code, NULL);
	return (msg_code);
}

static int	read_input(char **line)
{
	if (!line)
		return (ERR_CODE_READLINE_FAILED);
	print_message_by_code(MSH_CODE_PROMPT, NULL);
	if (*line)
		free(*line);
	*line = readline("");
	if (*line && **line)
		add_history(*line);
	return (SUCCESS);
}

// static char	*read_input(void)
// {
// 	char	*line;

// 	print_message_by_code(MSH_CODE_PROMPT, NULL);
// 	line = readline("");
// 	if (line && *line)
// 		add_history(line);
// 	return (line);
// }

static int	init_minishell(t_minishell *sh, char **envp)
{
	if (!sh)
		return (ERR_CODE_ENVINIT_FAILED);
	sh->ast = NULL;
	sh->token_list = NULL;
	sh->env = env_init(envp);
	if (!sh->env)
		return (ERR_CODE_ENVINIT_FAILED);
	return (SUCCESS);
}

int	run_minishell(char **envp)
{
	char		*line;
	t_minishell	sh;

	line = NULL;
	if (init_minishell(&sh, envp))
		return (exit_minishell(&sh, ERR_CODE_ENVINIT_FAILED));
	while (TRUE)
	{
		sh.env->last_status = read_input(&line);
		if (SUCCESS != sh.env->last_status)
			return (exit_minishell(&sh, sh.env->last_status));
		sh.env->last_status = handle_input(&sh, line);
		clean_shell(&sh, FALSE);
		if (EXIT_CODE_SIGNALLED == sh.env->last_status)
			return (exit_minishell(&sh, sh.env->last_status));
	}
}

// int	run_minishell(char **envp)
// {
// 	char		*line;
// 	t_minishell	sh;
	
// 	if (init_minishell(&sh, envp))
// 		return (exit_minishell(&sh, ERR_CODE_ENV_INIT));
// 	while (TRUE)
// 	{
// 		line = read_input();
// 		if (!line)
// 			return (exit_minishell(&sh, ERR_CODE_READLINE_FAILED));
// 		sh.env->last_status = handle_input(&sh, line);
// 		free(line);
// 		clean_shell(&sh, FALSE);
// 		if (EXIT_CODE_SIGNALLED == sh.env->last_status)
// 			return (exit_minishell(&sh, MSH_CODE_EXIT_EOF));
// 	}
// }
