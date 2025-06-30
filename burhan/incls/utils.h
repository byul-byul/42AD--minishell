/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:37:51 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/29 13:37:39 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define SUCCESS	0
# define PROD_MODE	0
# define DEBUG_MODE	1

# ifndef PROGRAM_MODE
#  define PROGRAM_MODE DEBUG_MODE
# endif

# define EXIT_CODE_SIGNALLED				999

// Prompts and UI
# define MSH_MSG_DEF_PROMPT				"minishell$ "
# define MSH_MSG_EXIT_ON_EOF			"exit\n"

// Signals
# define MSH_MSG_SIGINT_NEWLINE			"\n"
# define MSH_MSG_SIGQUIT_DUMPED			"Quit (core dumped)\n"
# define MSH_MSG_SIGQUIT_IGNORED		""

// Builtins
# define MSH_MSG_EXIT_NUMERIC_ARG		"minishell: exit: numeric argument required\n"
# define MSH_MSG_EXIT_TOO_MANY_ARGS		"minishell: exit: too many arguments\n"
# define MSH_MSG_CD_NO_HOME				"minishell: cd: HOME not set\n"
# define MSH_MSG_PWD_ERR				"minishell: pwd: error retrieving current directory\n"

// Errors
# define MSH_ERR_MSG_NONE				""
# define MSH_ERR_MSG_UNKNOWN			"minishell: unknown error\n"
# define MSH_ERR_MSG_REDIR				"minishell: redirection error\n"
# define MSH_ERR_MSG_SYNTAX				"minishell: syntax error near unexpected token `%s'\n"
# define MSH_ERR_MSG_CMD_NOT_FOUND		"minishell: %s: command not found\n"
# define MSH_ERR_MSG_NO_SUCH_FILE		"minishell: %s: No such file or directory\n"
# define MSH_ERR_MSG_IS_DIR				"minishell: %s: is a directory\n"
# define MSH_ERR_MSG_NOT_EXECUTABLE		"minishell: %s: Permission denied\n"
# define MSH_ERR_MSG_FORK_FAILED		"minishell: fork: Resource temporarily unavailable\n"
# define MSH_ERR_MSG_EXECVE_FAILED		"minishell: execve failed\n"
# define MSH_ERR_MSG_ENV_INIT			"minishell: failed to initialize environment\n"
# define MSH_ERR_MSG_MALLOC				"minishell: memory allocation failed\n"
# define MSH_ERR_MSG_READLINE_FAILED	"minishell: readline() returned NULL\n"

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
	ERR_CODE_NONE = -100,
	ERR_CODE_UNKNOWN,
	ERR_CODE_REDIR,
	ERR_CODE_SYNTAX,
	ERR_CODE_CMD_NOT_FOUND,
	ERR_CODE_NO_SUCH_FILE,
	ERR_CODE_IS_DIR,
	ERR_CODE_NOT_EXECUTABLE,
	ERR_CODE_FORK_FAILED,
	ERR_CODE_EXECVE_FAILED,
	ERR_CODE_ENVINIT_FAILED,
	ERR_CODE_MALLOC,
	ERR_CODE_READLINE_FAILED,
}	t_error_code;

typedef enum e_msg_group
{
	ERR_CODE_GROUP_01 = -90,
	ERR_CODE_GROUP_02 = -80,
}	t_msg_group;

#endif