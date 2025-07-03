/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:37:51 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 19:35:52 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

# define SUCCESS				0
# define ERR_CODE_STARTS_AT		101
# define EXIT_CODE_SIGNALLED	999

# define PROD_MODE				0
# define DEBUG_MODE				1

# ifndef PROGRAM_MODE
#  define PROGRAM_MODE PROD_MODE
# endif

// MWM - minishell work message
// Prompts and UI;
# define MWM_EMPTY				""
# define MWM_UNKNOWN			"unknown message\n"
# define MWM_DEFAULT_PROMPT		"minishell$ "
# define MWM_DEFAULT_PREFIX		"minishell: "
# define MWM_EXIT_ON_EOF		"exit\n"

// MEM - minishell error message
// Errors;
# define MEM_UNKNOWN			"unknown error\n"
# define MEM_ENVINIT_FAILED		"failed to initialize environment\n"
# define MEM_READLINE_FAILED	"readline() returned NULL\n"
# define MEM_LEXER_FAILED		"lexer() returned NULL\n"
# define MEM_EXPANDER_FAILED	"expander() returned NULL\n"
# define MEM_PARSER_FAILED		"parser() returned NULL\n"

# define MEM_PARSER_SYNTAX_00	"syntax error near unexpected token `"
# define MEM_PARSER_SYNTAX_01	"expected `"

typedef enum e_msg_group
{
	MSG_GROUP_00 = 10,
	MSG_GROUP_10 = 110,
}	t_msg_group;

typedef enum e_msg_code
{
	MSH_CODE_UNKNOWN,
	MSH_CODE_DEF_PROMPT,
	MSH_CODE_DEF_PREFIX,
	MSH_CODE_EXIT_ON_EOF,
}	t_msg_code;

typedef enum e_error_code
{
	ERR_CODE_UNKNOWN = ERR_CODE_STARTS_AT,
	ERR_CODE_ENVINIT_FAILED,
	ERR_CODE_READLINE_FAILED,
	ERR_CODE_LEXER_FAILED,
	ERR_CODE_EXPANDER_FAILED,
	ERR_CODE_PARSER_FAILED,
	ERR_CODE_PARSER_SYNTAX_00,
	ERR_CODE_PARSER_SYNTAX_01,
}	t_error_code;

void	print_msg_by_code(int msg_code, const char *msg_part);

#endif