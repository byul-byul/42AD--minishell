/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:37:51 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/30 23:27:03 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

# define SUCCESS	0
# define PROD_MODE	0
# define DEBUG_MODE	1

# ifndef PROGRAM_MODE
#  define PROGRAM_MODE DEBUG_MODE
# endif

# define EXIT_CODE_SIGNALLED	999

// Prompts and UI; MWM - minishell work message
# define MWM_DEF_PROMPT			"minishell$ "
# define MWM_EXIT_ON_EOF		"exit\n"
# define MWM_DEFAULT_PREFIX		"minishell: "

// Signals; MWM - minishell work message
# define MWM_SIGINT_NEWLINE		"\n"
# define MWM_SIGQUIT_DUMPED		"Quit (core dumped)\n"
# define MWM_SIGQUIT_IGNORED	""

// Builtins; MWM - minishell work message
# define MWM_EXIT_NUMERIC_ARG	"exit: numeric argument required\n"
# define MWM_EXIT_TOO_MANY_ARGS	"exit: too many arguments\n"
# define MWM_CD_NO_HOME			"cd: HOME not set\n"
# define MWM_PWD_ERR			"pwd: error retrieving current directory\n"

// Errors; MEM - minishell error message
# define MEM_UNKNOWN			"unknown error\n"
# define MEM_ENVINIT_FAILED		"failed to initialize environment\n"
# define MEM_READLINE_FAILED	"readline() returned NULL\n"
# define MEM_LEXER_FAILED		"lexer() returned NULL\n"
# define MEM_EXPANDER_FAILED	"expander() returned NULL\n"
# define MEM_PARSER_FAILED		"parser() returned NULL\n"

typedef enum e_msg_code
{
	MSH_CODE_PROMPT,
	MSH_CODE_EXIT_EOF,
	MSH_CODE_SIGINT_NEWLINE,
	MSH_CODE_SIGQUIT_DUMPED,
	MSH_CODE_SIGQUIT_IGNORED,
	MSH_CODE_EXIT_NUMERIC_ARG,
	MSH_CODE_EXIT_TOO_MANY_ARGS,
	MSH_CODE_CD_NO_HOME,
	MSH_CODE_PWD_ERR,
}	t_msg_code;

typedef enum e_error_code
{
	ERR_CODE_UNKNOWN = -100,
	ERR_CODE_ENVINIT_FAILED,
	ERR_CODE_READLINE_FAILED,
	ERR_CODE_LEXER_FAILED,
	ERR_CODE_EXPANDER_FAILED,
	ERR_CODE_PARSER_FAILED,
}	t_error_code;

void	minishell_printf(int msg_code, const char *msg_part);
void	printf_msg_by_code(int msg_code, const char *msg_part);

#endif