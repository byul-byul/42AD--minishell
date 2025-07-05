/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oqaroot <oqaroot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:35:16 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/04 17:43:30 by oqaroot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_wrapper.h"

static int	exit_minishell(t_minishell *sh, int exit_code)
{
	clean_shell(sh, TRUE);
	print_msg_by_code(exit_code, NULL);
	return (exit_code);
}

static int	handle_input(t_minishell *sh, char *line)
{
	if (!ft_strlen(line))
		return (SUCCESS);
	sh->token_list = lexer(line);
	if (!sh->token_list)
		return (ERR_CODE_LEXER_FAILED);
	if (PROGRAM_MODE == DEBUG_MODE)
		print_lexer_result(line, sh->token_list);
	sh->token_list = expander(sh->token_list, sh->env);
	if (!sh->token_list)
		return (ERR_CODE_EXPANDER_FAILED);
	if (PROGRAM_MODE == DEBUG_MODE)
		print_expander_result(sh->token_list);
	sh->ast = parser(sh->token_list);
	if (!sh->ast)
		return (ERR_CODE_PARSER_FAILED);
	if (PROGRAM_MODE == DEBUG_MODE)
		print_parser_result(sh->ast);
	return (exec_ast(sh->ast, sh->env));
}

static int	read_input(char **line)
{
	if (!line)
		return (ERR_CODE_READLINE_FAILED);
	*line = readline(MWM_DEFAULT_PROMPT);
	if (!*line)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_putstr_fd(MWM_EXIT_ON_EOF, STDOUT_FILENO);
		return (EXIT_CODE_SIGNALLED);
	}
	if (**line)
		add_history(*line);
	return (SUCCESS);
}

static int	init_minishell(t_minishell *sh, char **envp)
{
	if (!sh)
		return (ERR_CODE_UNKNOWN);
	sh->ast = NULL;
	sh->token_list = NULL;
	sh->input = NULL;
	sh->env = env_init(envp);
	if (!sh->env)
		return (ERR_CODE_ENVINIT_FAILED);
	return (SUCCESS);
}

int	run_minishell(char **envp)
{
	int			res;
	t_minishell	sh;

	res = init_minishell(&sh, envp);
	if (SUCCESS != res)
		return (exit_minishell(&sh, res));
	setup_shell_signals();
	signal(SIGQUIT, SIG_IGN);
	while (TRUE)
	{
		sh.env->last_status = read_input(&sh.input);
		if (SUCCESS != sh.env->last_status)
			return (exit_minishell(&sh, sh.env->last_status));
		sh.env->last_status = handle_input(&sh, sh.input);
		g_exit_status = sh.env->last_status;
		clean_shell(&sh, FALSE);
		if (EXIT_CODE_SIGNALLED == sh.env->last_status)
			return (exit_minishell(&sh, sh.env->last_status));
	}
}
