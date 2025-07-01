/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils_00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 18:05:49 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 00:01:28 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_wrapper.h"

static const char	*get_msg_by_code_00(int msg_code)
{
	if (MSH_CODE_DEF_PROMPT == msg_code)
		return (MWM_DEFAULT_PROMPT);
	else if (MSH_CODE_DEF_PREFIX == msg_code)
		return (MWM_DEFAULT_PREFIX);
	else if (MSH_CODE_EXIT_ON_EOF == msg_code)
		return (MWM_EXIT_ON_EOF);
	return (MWM_UNKNOWN);
}

static const char	*get_msg_by_code_10(int msg_code)
{
	if (ERR_CODE_ENVINIT_FAILED == msg_code)
		return (MEM_ENVINIT_FAILED);
	else if (ERR_CODE_READLINE_FAILED == msg_code)
		return (MEM_READLINE_FAILED);
	else if (ERR_CODE_LEXER_FAILED == msg_code)
		return (MEM_LEXER_FAILED);
	else if (ERR_CODE_EXPANDER_FAILED == msg_code)
		return (MEM_EXPANDER_FAILED);
	else if (ERR_CODE_PARSER_FAILED == msg_code)
		return (MEM_PARSER_FAILED);
	else if (ERR_CODE_PARSER_SYNTAX_00 == msg_code)
		return (MEM_PARSER_SYNTAX_00);
	else if (ERR_CODE_PARSER_SYNTAX_01 == msg_code)
		return (MEM_PARSER_SYNTAX_01);
	return (MEM_UNKNOWN);
}

static const char	*get_msg_by_code(int msg_code)
{
	if (msg_code < MSG_GROUP_00)
		return (get_msg_by_code_00(msg_code));
	else if (msg_code < MSG_GROUP_10)
		return (get_msg_by_code_10(msg_code));
	else if (msg_code == EXIT_CODE_SIGNALLED)
		return (MWM_EMPTY);
	return (MEM_UNKNOWN);
}

static void	print_msg(int fd, int msg_code, const char *msg_part)
{
	ft_putstr_fd(get_msg_by_code(MSH_CODE_DEF_PREFIX), fd);
	ft_putstr_fd(get_msg_by_code(msg_code), fd);
	if (msg_part)
	{
		ft_putstr_fd(msg_part, fd);
		ft_putchar_fd('\n', fd);
	}
}

void	print_msg_by_code(int msg_code, const char *msg_part)
{
	if (msg_code < ERR_CODE_STARTS_AT)
		print_msg(1, msg_code, msg_part);
	else
		print_msg(2, msg_code, msg_part);
}
