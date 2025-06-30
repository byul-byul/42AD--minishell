/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:05:49 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/30 23:27:39 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_wrapper.h"

static void	print_err_msg(int msg_code, const char *msg_part)
{
	(void)msg_part;
	if (ERR_CODE_UNKNOWN == msg_code)
		ft_printf(MEM_UNKNOWN);
	else if (ERR_CODE_ENVINIT_FAILED == msg_code)
		ft_printf(MEM_ENVINIT_FAILED);
	else if (ERR_CODE_READLINE_FAILED == msg_code)
		ft_printf(MEM_READLINE_FAILED);
	else if (ERR_CODE_LEXER_FAILED == msg_code)
		ft_printf(MEM_LEXER_FAILED);
	else if (ERR_CODE_EXPANDER_FAILED == msg_code)
		ft_printf(MEM_EXPANDER_FAILED);
	else if (ERR_CODE_PARSER_FAILED == msg_code)
		ft_printf(MEM_PARSER_FAILED);
}

static void	print_work_msg(int msg_code, const char *msg_part)
{
	(void)msg_part;
	if (MSH_CODE_PROMPT == msg_code)
		ft_printf(MWM_DEF_PROMPT);
	else if (MSH_CODE_EXIT_EOF == msg_code)
		ft_printf(MWM_EXIT_ON_EOF);
	else if (MSH_CODE_SIGINT_NEWLINE == msg_code)
		ft_printf(MWM_SIGINT_NEWLINE);
	else if (MSH_CODE_SIGQUIT_DUMPED == msg_code)
		ft_printf(MWM_SIGQUIT_DUMPED);
	else if (MSH_CODE_SIGQUIT_IGNORED == msg_code)
		ft_printf(MWM_SIGQUIT_IGNORED);
	else if (MSH_CODE_EXIT_NUMERIC_ARG == msg_code)
		ft_printf(MWM_EXIT_NUMERIC_ARG);
	else if (MSH_CODE_EXIT_TOO_MANY_ARGS == msg_code)
		ft_printf(MWM_EXIT_TOO_MANY_ARGS);
	else if (MSH_CODE_CD_NO_HOME == msg_code)
		ft_printf(MWM_CD_NO_HOME);
	else if (MSH_CODE_PWD_ERR == msg_code)
		ft_printf(MWM_PWD_ERR);
}

void	printf_msg_by_code(int msg_code, const char *msg_part)
{
	if (msg_code < 0)
		print_err_msg(msg_code, msg_part);
	else
		print_work_msg(msg_code, msg_part);
}

void	minishell_printf(int msg_code, const char *msg_part)
{
	ft_printf(MWM_DEF_PROMPT);
	printf_msg_by_code(msg_code, msg_part);
}
