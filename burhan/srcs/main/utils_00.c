/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:39:32 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 10:17:51 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_wrapper.h"

static void	print_err_msg_group_01(int msg_code, const char *msg_part)
{
	if (ERR_CODE_NONE == msg_code)
		ft_printf(MSH_ERR_MSG_NONE);
	else if (ERR_CODE_UNKNOWN == msg_code)
		ft_printf(MSH_ERR_MSG_UNKNOWN);
	else if (ERR_CODE_REDIR == msg_code)
		ft_printf(MSH_ERR_MSG_REDIR);
	else if (ERR_CODE_SYNTAX == msg_code)
		ft_printf(MSH_ERR_MSG_SYNTAX, msg_part);
	else if (ERR_CODE_CMD_NOT_FOUND == msg_code)
		ft_printf(MSH_ERR_MSG_CMD_NOT_FOUND, msg_part);
	else if (ERR_CODE_NO_SUCH_FILE == msg_code)
		ft_printf(MSH_ERR_MSG_NO_SUCH_FILE, msg_part);
	else if (ERR_CODE_IS_DIR == msg_code)
		ft_printf(MSH_ERR_MSG_IS_DIR, msg_part);
	else if (ERR_CODE_NOT_EXECUTABLE == msg_code)
		ft_printf(MSH_ERR_MSG_NOT_EXECUTABLE, msg_part);
	else if (ERR_CODE_FORK_FAILED == msg_code)
		ft_printf(MSH_ERR_MSG_FORK_FAILED);
	else if (ERR_CODE_EXECVE_FAILED == msg_code)
		ft_printf(MSH_ERR_MSG_EXECVE_FAILED);
	else if (ERR_CODE_ENVINIT_FAILED == msg_code)
		ft_printf(MSH_ERR_MSG_ENV_INIT);
	else if (ERR_CODE_MALLOC == msg_code)
		ft_printf(MSH_ERR_MSG_MALLOC);
	else if (ERR_CODE_READLINE_FAILED == msg_code)
		ft_printf(MSH_ERR_MSG_READLINE_FAILED);
}

static void	print_work_msg_group_01(int msg_code, char *msg_part)
{
	(void)msg_part;
	if (MSH_CODE_PROMPT == msg_code)
		ft_printf(MSH_MSG_DEF_PROMPT);
	else if (MSH_CODE_EXIT_EOF == msg_code)
		ft_printf(MSH_MSG_EXIT_ON_EOF);
	else if (MSH_CODE_SIGINT_NEWLINE == msg_code)
		ft_printf(MSH_MSG_SIGINT_NEWLINE);
	else if (MSH_CODE_SIGQUIT_DUMPED == msg_code)
		ft_printf(MSH_MSG_SIGQUIT_DUMPED);
	else if (MSH_CODE_SIGQUIT_IGNORED == msg_code)
		ft_printf(MSH_MSG_SIGQUIT_IGNORED);
	else if (MSH_CODE_EXIT_NUMERIC_ARG == msg_code)
		ft_printf(MSH_MSG_EXIT_NUMERIC_ARG);
	else if (MSH_CODE_EXIT_TOO_MANY_ARGS == msg_code)
		ft_printf(MSH_MSG_EXIT_TOO_MANY_ARGS);
	else if (MSH_CODE_CD_NO_HOME == msg_code)
		ft_printf(MSH_MSG_CD_NO_HOME);
	else if (MSH_CODE_PWD_ERR == msg_code)
		ft_printf(MSH_MSG_PWD_ERR);
}

void	print_message_by_code(int msg_code, char *msg_part)
{
	if (msg_code < 0)
	{
		if (msg_code <= GROUP_01)
			print_err_msg_group_01(msg_code, msg_part);
	}
	else
	{
		if (msg_code <= GROUP_01)
			print_work_msg_group_01(msg_code, msg_part);
	}
}

void	clean_shell(t_minishell *sh, int clean_env)
{
	if (!sh)
		return ;
	if (sh->env && clean_env)
	{
		env_free(sh->env);
		sh->env = NULL;
	}
	if (sh->token_list)
	{
		clean_token_list(sh->token_list);
		sh->token_list = NULL;
	}
	if (sh->ast)
	{
		free_ast(sh->ast);
		sh->ast = NULL;
	}
}
