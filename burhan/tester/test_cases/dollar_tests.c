/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 07:17:31 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 15:35:57 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

const t_test_case dollar_tests[] =
{
	// SIMPLE CASES
	{
		.input = "echo $USER",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER'",
		.expected_parser = "[CMD] echo $USER",
		.expected_expander = "WORD -> 'echo', WORD -> 'byulbyul'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── byulbyul"
	},
	{
		.input = "echo $?",
		.expected_lexer = "WORD -> 'echo', WORD -> '$?'",
		.expected_parser = "[CMD] echo $?",
		.expected_expander = "WORD -> 'echo', WORD -> '0'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── 0"
	},
	{
		.input = "echo $1",
		.expected_lexer = "WORD -> 'echo', WORD -> '$1'",
		.expected_parser = "[CMD] echo $1",
		.expected_expander = "WORD -> 'echo', WORD -> '$1'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $1"
	},
	{
		.input = "echo $$",
		.expected_lexer = "WORD -> 'echo', WORD -> '$$'",
		.expected_parser = "[CMD] echo $$",
		.expected_expander = "WORD -> 'echo', WORD -> '$$'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $$"
	},
	{
		.input = "echo $@",
		.expected_lexer = "WORD -> 'echo', WORD -> '$@'",
		.expected_parser = "[CMD] echo $@",
		.expected_expander = "WORD -> 'echo', WORD -> '$@'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $@"
	},
	{
		.input = "echo $*",
		.expected_lexer = "WORD -> 'echo', WORD -> '$*'",
		.expected_parser = "[CMD] echo $*",
		.expected_expander = "WORD -> 'echo', WORD -> '$*'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $*"
	},
	// EMPTY DOLLAR
	{
		.input = "echo $",
		.expected_lexer = "WORD -> 'echo', WORD -> '$'",
		.expected_parser = "[CMD] echo $",
		.expected_expander = "WORD -> 'echo', WORD -> '$'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $"
	},
	{
		.input = "echo $ ",
		.expected_lexer = "WORD -> 'echo', WORD -> '$'",
		.expected_parser = "[CMD] echo $",
		.expected_expander = "WORD -> 'echo', WORD -> '$'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $"
	},
	// MULTIPLE VARIABLES TOGETHER
	{
		.input = "echo $VAR$VAR2",
		.expected_lexer = "WORD -> 'echo', WORD -> '$VAR$VAR2'",
		.expected_parser = "[CMD] echo $VAR$VAR2",
		.expected_expander = "WORD -> 'echo', WORD -> ''",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── "
	},
	{
		.input = "echo $VAR_$VAR2",
		.expected_lexer = "WORD -> 'echo', WORD -> '$VAR_$VAR2'",
		.expected_parser = "[CMD] echo $VAR_$VAR2",
		.expected_expander = "WORD -> 'echo', WORD -> ''",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── "
	},
	// WITH CURLY BRACES
	{
		.input = "echo ${USER}",
		.expected_lexer = "WORD -> 'echo', WORD -> '${USER}'",
		.expected_parser = "[CMD] echo ${USER}",
		.expected_expander = "WORD -> 'echo', WORD -> '${USER}'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── ${USER}"
	},
	{
		.input = "echo ${}",
		.expected_lexer = "WORD -> 'echo', WORD -> '${}'",
		.expected_parser = "[CMD] echo ${}",
		.expected_expander = "WORD -> 'echo', WORD -> '${}'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── ${}"
	},
	{
		.input = "echo ${USER$ID}",
		.expected_lexer = "WORD -> 'echo', WORD -> '${USER$ID}'",
		.expected_parser = "[CMD] echo ${USER$ID}",
		.expected_expander = "WORD -> 'echo', WORD -> '${USER}'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── ${USER}"
	},
	// INSIDE QUOTES
	{
		.input = "echo '$USER'",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER'",
		.expected_parser = "[CMD] echo '$USER'",
		.expected_expander = "WORD -> 'echo', WORD -> '$USER'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $USER"
	},
	{
		.input = "echo \"$USER\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER'",
		.expected_parser = "[CMD] echo \"$USER\"",
		.expected_expander = "WORD -> 'echo', WORD -> 'byulbyul'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── byulbyul"
	},
	{
		.input = "echo \"$USER$HOME\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER$HOME'",
		.expected_parser = "[CMD] echo \"$USER$HOME\"",
		.expected_expander = "WORD -> 'echo', WORD -> 'byulbyul/home/byulbyul'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── byulbyul/home/byulbyul"
	},
	{
		.input = "echo '$USER$HOME'",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER$HOME'",
		.expected_parser = "[CMD] echo '$USER$HOME'",
		.expected_expander = "WORD -> 'echo', WORD -> '$USER$HOME'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $USER$HOME"
	},
	// ESCAPED DOLLARS
	{
		.input = "echo \\$USER",
		.expected_lexer = "WORD -> 'echo', WORD -> '\\$USER'",
		.expected_parser = "[CMD] echo $USER",
		.expected_expander = "WORD -> 'echo', WORD -> '$USER'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $USER"
	},
	{
		.input = "echo \\$?",
		.expected_lexer = "WORD -> 'echo', WORD -> '\\$?'",
		.expected_parser = "[CMD] echo $?",
		.expected_expander = "WORD -> 'echo', WORD -> '$?'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $?"
	},
	// MIXED / COMPLEX CASES
	{
		.input = "echo \"Path: $PATH\"",
		.expected_lexer = "WORD -> 'echo', WORD -> 'Path: $PATH'",
		.expected_parser = "[CMD] echo \"Path: $PATH\"",
		.expected_expander = "WORD -> 'echo', WORD -> 'Path: /usr/bin:/bin'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── Path: /usr/bin:/bin"
	},
	{
		.input = "echo 'Path: $PATH'",
		.expected_lexer = "WORD -> 'echo', WORD -> 'Path: $PATH'",
		.expected_parser = "[CMD] echo 'Path: $PATH'",
		.expected_expander = "WORD -> 'echo', WORD -> 'Path: $PATH'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── Path: $PATH"
	},
	{
		.input = "echo ${UNFINISHED",
		.expected_lexer = "WORD -> 'echo', WORD -> '${UNFINISHED'",
		.expected_parser = "[CMD] echo ${UNFINISHED",
		.expected_expander = "WORD -> 'echo', WORD -> '${UNFINISHED'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── ${UNFINISHED"
	},
	{
		.input = "echo $123abc",
		.expected_lexer = "WORD -> 'echo', WORD -> '$123abc'",
		.expected_parser = "[CMD] echo $123abc",
		.expected_expander = "WORD -> 'echo', WORD -> '$123abc'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $123abc"
	},

	// ISOLATED DOLLARS
	{
		.input = "$",
		.expected_lexer = "WORD -> '$'",
		.expected_parser = "[CMD] $",
		.expected_expander = "WORD -> '$'",
		.expected_ast =
			"CMD\n"
			"└── $"
	},
	{
		.input = "$$",
		.expected_lexer = "WORD -> '$$'",
		.expected_parser = "[CMD] $$",
		.expected_expander = "WORD -> '$$'",
		.expected_ast =
			"CMD\n"
			"└── $$"
	},
	{
		.input = "$?",
		.expected_lexer = "WORD -> '$?'",
		.expected_parser = "[CMD] $?",
		.expected_expander = "WORD -> '0'",
		.expected_ast =
			"CMD\n"
			"└── 0"
	},
	// MERGED VARIABLE CASES
	{
		.input = "echo \"$VARtext\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '$VARtext'",
		.expected_parser = "[CMD] echo \"$VARtext\"",
		.expected_expander = "WORD -> 'echo', WORD -> ''",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└──"
	},
	{
		.input = "echo \"abc$VARxyz\"",
		.expected_lexer = "WORD -> 'echo', WORD -> 'abc$VARxyz'",
		.expected_parser = "[CMD] echo \"abc$VARxyz\"",
		.expected_expander = "WORD -> 'echo', WORD -> 'abc'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── abc"
	},
	{
		.input = "echo \"${VAR}suffix\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '${VAR}suffix'",
		.expected_parser = "[CMD] echo \"${VAR}suffix\"",
		.expected_expander = "WORD -> 'echo', WORD -> '${VAR}suffix'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── ${VAR}suffix"
	},
	{
		.input = "\"a\"'$b'\"c\"",
		.expected_lexer = "WORD -> 'a$bc'",
		.expected_expander = "WORD -> 'a$bc'",
		.expected_parser = "[CMD] a$bc",
		.expected_ast =
			"AST_NODE_CMD\n"
			"  CMD: a$bc\n"
	}
};

const t_test_block dollar_block = {
	.block_name = "DOLLAR EXPANSION TESTS",
	.block_label = "dollar sign $",
	.cases = dollar_tests,
	.count = sizeof(dollar_tests) / sizeof(dollar_tests[0])
};
