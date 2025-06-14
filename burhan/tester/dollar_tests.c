/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 07:17:31 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/14 21:03:16 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dollar_block.c

#include "tester.h"
#include <stdlib.h>

const t_test_case dollar_tests[] =
{
	// SIMPLE CASES
	{
		.input = "echo $USER",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER'",
		.expected_parser = "[CMD] echo $USER"
	},
	{
		.input = "echo $?",
		.expected_lexer = "WORD -> 'echo', WORD -> '$?'",
		.expected_parser = "[CMD] echo $?"
	},
	{
		.input = "echo $1",
		.expected_lexer = "WORD -> 'echo', WORD -> '$1'",
		.expected_parser = "[CMD] echo $1"
	},
	{
		.input = "echo $$",
		.expected_lexer = "WORD -> 'echo', WORD -> '$$'",
		.expected_parser = "[CMD] echo $$"
	},
	{
		.input = "echo $@",
		.expected_lexer = "WORD -> 'echo', WORD -> '$@'",
		.expected_parser = "[CMD] echo $@"
	},
	{
		.input = "echo $*",
		.expected_lexer = "WORD -> 'echo', WORD -> '$*'",
		.expected_parser = "[CMD] echo $*"
	},

	// EMPTY DOLLAR
	{
		.input = "echo $",
		.expected_lexer = "WORD -> 'echo', WORD -> '$'",
		.expected_parser = "[CMD] echo $"
	},
	{
		.input = "echo $ ",
		.expected_lexer = "WORD -> 'echo', WORD -> '$'",
		.expected_parser = "[CMD] echo $"
	},

	// MULTIPLE VARIABLES TOGETHER
	{
		.input = "echo $VAR$VAR2",
		.expected_lexer = "WORD -> 'echo', WORD -> '$VAR$VAR2'",
		.expected_parser = "[CMD] echo $VAR$VAR2"
	},
	{
		.input = "echo $VAR_$VAR2",
		.expected_lexer = "WORD -> 'echo', WORD -> '$VAR_$VAR2'",
		.expected_parser = "[CMD] echo $VAR_$VAR2"
	},

	// WITH CURLY BRACES
	{
		.input = "echo ${USER}",
		.expected_lexer = "WORD -> 'echo', WORD -> '${USER}'",
		.expected_parser = "[CMD] echo ${USER}"
	},
	{
		.input = "echo ${}",
		.expected_lexer = "WORD -> 'echo', WORD -> '${}'",
		.expected_parser = "[CMD] echo ${}"
	},
	{
		.input = "echo ${USER$ID}",
		.expected_lexer = "WORD -> 'echo', WORD -> '${USER$ID}'",
		.expected_parser = "[CMD] echo ${USER$ID}"
	},

	// INSIDE QUOTES
	{
		.input = "echo '$USER'",
		.expected_lexer = "WORD -> 'echo', WORD (quoted=SINGLE) -> '$USER'",
		.expected_parser = "[CMD] echo '$USER'"
	},
	{
		.input = "echo \"$USER\"",
		.expected_lexer = "WORD -> 'echo', WORD (quoted=DOUBLE, expanded) -> '$USER'",
		.expected_parser = "[CMD] echo \"$USER\""
	},
	{
		.input = "echo \"$USER$HOME\"",
		.expected_lexer = "WORD -> 'echo', WORD (quoted=DOUBLE, expanded) -> '$USER$HOME'",
		.expected_parser = "[CMD] echo \"$USER$HOME\""
	},
	{
		.input = "echo '$USER$HOME'",
		.expected_lexer = "WORD -> 'echo', WORD (quoted=SINGLE) -> '$USER$HOME'",
		.expected_parser = "[CMD] echo '$USER$HOME'"
	},

	// ESCAPED DOLLARS
	{
		.input = "echo \\$USER",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER'",
		.expected_parser = "[CMD] echo $USER"
	},
	{
		.input = "echo \\$?",
		.expected_lexer = "WORD -> 'echo', WORD -> '$?'",
		.expected_parser = "[CMD] echo $?"
	},

	// MIXED / COMPLEX CASES
	{
		.input = "echo \"Path: $PATH\"",
		.expected_lexer = "WORD -> 'echo', WORD (quoted=DOUBLE, expanded) -> 'Path: $PATH'",
		.expected_parser = "[CMD] echo \"Path: $PATH\""
	},
	{
		.input = "echo 'Path: $PATH'",
		.expected_lexer = "WORD -> 'echo', WORD (quoted=SINGLE) -> 'Path: $PATH'",
		.expected_parser = "[CMD] echo 'Path: $PATH'"
	},
	{
		.input = "echo ${UNFINISHED",
		.expected_lexer = "WORD -> 'echo', WORD -> '${UNFINISHED'",
		.expected_parser = "[CMD] echo ${UNFINISHED"
	},
	{
		.input = "echo $123abc",
		.expected_lexer = "WORD -> 'echo', WORD -> '$123abc'",
		.expected_parser = "[CMD] echo $123abc"
	},

	// ISOLATED DOLLARS
	{
		.input = "$",
		.expected_lexer = "WORD -> '$'",
		.expected_parser = "[CMD] $"
	},
	{
		.input = "$$",
		.expected_lexer = "WORD -> '$$'",
		.expected_parser = "[CMD] $$"
	},
	{
		.input = "$?",
		.expected_lexer = "WORD -> '$?'",
		.expected_parser = "[CMD] $?"
	}

};

const t_test_block dollar_block = {
	.block_name = "DOLLAR EXPANSION TESTS",
	.block_label = "dollar sign $",
	.cases = dollar_tests,
	.count = sizeof(dollar_tests) / sizeof(dollar_tests[0])
};
