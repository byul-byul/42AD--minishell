/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paren_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:25:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 13:10:56 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

const t_test_case paren_tests[] =
{
	// PARENTHESIS CASES
	{
		.input = "(true)",
		.expected_lexer = "OPEN_PAREN -> '(', WORD -> 'true', CLOSE_PAREN -> ')'",
		.expected_expander = "OPEN_PAREN -> '(', WORD -> 'true', CLOSE_PAREN -> ')'",
		.expected_parser = "( true )",
		.expected_ast =
			"SUBSHELL\n"
			"└── CMD\n"
			"    └── true"
	},
	{
		.input = "((cmd))",
		.expected_lexer = "OPEN_PAREN -> '(', OPEN_PAREN -> '(', WORD -> 'cmd', CLOSE_PAREN -> ')', CLOSE_PAREN -> ')'",
		.expected_expander = "OPEN_PAREN -> '(', OPEN_PAREN -> '(', WORD -> 'cmd', CLOSE_PAREN -> ')', CLOSE_PAREN -> ')'",
		.expected_parser = "( ( cmd ) )",
		.expected_ast =
			"SUBSHELL\n"
			"└── SUBSHELL\n"
			"    └── CMD\n"
			"        └── cmd"
	},
	{
		.input = "(",
		.expected_lexer = "OPEN_PAREN -> '('",
		.expected_expander = "OPEN_PAREN -> '('",
		.expected_parser = "(",
		.expected_ast = "SYNTAX_ERROR"
	},
	{
		.input = ")",
		.expected_lexer = "CLOSE_PAREN -> ')'",
		.expected_expander = "CLOSE_PAREN -> ')'",
		.expected_parser = ")",
		.expected_ast = "SYNTAX_ERROR"
	},
	{
		.input = "())",
		.expected_lexer = "OPEN_PAREN -> '(', CLOSE_PAREN -> ')', CLOSE_PAREN -> ')'",
		.expected_expander = "OPEN_PAREN -> '(', CLOSE_PAREN -> ')', CLOSE_PAREN -> ')'",
		.expected_parser = "( ) )",
		.expected_ast = "SYNTAX_ERROR"
	},
	{
		.input = "(cmd",
		.expected_lexer = "OPEN_PAREN -> '(', WORD -> 'cmd'",
		.expected_expander = "OPEN_PAREN -> '(', WORD -> 'cmd'",
		.expected_parser = "( cmd",
		.expected_ast = "SYNTAX_ERROR"
	},
	// PARENTHESIS EXTENDED CASES
	{
		.input = "(echo a) | (echo b)",
		.expected_lexer = "OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'a', CLOSE_PAREN -> ')', PIPE -> '|', OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'b', CLOSE_PAREN -> ')'",
		.expected_expander = "OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'a', CLOSE_PAREN -> ')', PIPE -> '|', OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'b', CLOSE_PAREN -> ')'",
		.expected_parser = "( echo a ) | ( echo b )",
		.expected_ast =
			"PIPE\n"
			"├── SUBSHELL\n"
			"│   └── CMD\n"
			"│       ├── echo\n"
			"│       └── a\n"
			"└── SUBSHELL\n"
			"    └── CMD\n"
			"        ├── echo\n"
			"        └── b"
	},
	{
		.input = "(ls && pwd) || (echo fail)",
		.expected_lexer = "OPEN_PAREN -> '(', WORD -> 'ls', AND -> '&&', WORD -> 'pwd', CLOSE_PAREN -> ')', OR -> '||', OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'fail', CLOSE_PAREN -> ')'",
		.expected_expander = "OPEN_PAREN -> '(', WORD -> 'ls', AND -> '&&', WORD -> 'pwd', CLOSE_PAREN -> ')', OR -> '||', OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'fail', CLOSE_PAREN -> ')'",
		.expected_parser = "( ls && pwd ) || ( echo fail )",
		.expected_ast =
			"OR\n"
			"├── SUBSHELL\n"
			"│   └── AND\n"
			"│       ├── CMD\n"
			"│       │   └── ls\n"
			"│       └── CMD\n"
			"│           └── pwd\n"
			"└── SUBSHELL\n"
			"    └── CMD\n"
			"        ├── echo\n"
			"        └── fail"
	},
	{
		.input = "(echo hi) > out.txt",
		.expected_lexer = "OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'hi', CLOSE_PAREN -> ')', REDIR_OUT -> '>', WORD -> 'out.txt'",
		.expected_expander = "OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'hi', CLOSE_PAREN -> ')', REDIR_OUT -> '>', WORD -> 'out.txt'",
		.expected_parser = "( echo hi ) > out.txt",
		.expected_ast =
			"SUBSHELL\n"
			"└── CMD\n"
			"    ├── echo\n"
			"    └── hi\n"
			"> out.txt"
	},
	{
		.input = "((true) && (false))",
		.expected_lexer = "OPEN_PAREN -> '(', OPEN_PAREN -> '(', WORD -> 'true', CLOSE_PAREN -> ')', AND -> '&&', OPEN_PAREN -> '(', WORD -> 'false', CLOSE_PAREN -> ')', CLOSE_PAREN -> ')'",
		.expected_expander = "OPEN_PAREN -> '(', OPEN_PAREN -> '(', WORD -> 'true', CLOSE_PAREN -> ')', AND -> '&&', OPEN_PAREN -> '(', WORD -> 'false', CLOSE_PAREN -> ')', CLOSE_PAREN -> ')'",
		.expected_parser = "( ( true ) && ( false ) )",
		.expected_ast =
			"SUBSHELL\n"
			"└── AND\n"
			"    ├── SUBSHELL\n"
			"    │   └── CMD\n"
			"    │       └── true\n"
			"    └── SUBSHELL\n"
			"        └── CMD\n"
			"            └── false"
	},
	{
		.input = "(echo a && (echo b || echo c))",
		.expected_lexer = "OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'a', AND -> '&&', OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'b', OR -> '||', WORD -> 'echo', WORD -> 'c', CLOSE_PAREN -> ')', CLOSE_PAREN -> ')'",
		.expected_expander = "OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'a', AND -> '&&', OPEN_PAREN -> '(', WORD -> 'echo', WORD -> 'b', OR -> '||', WORD -> 'echo', WORD -> 'c', CLOSE_PAREN -> ')', CLOSE_PAREN -> ')'",
		.expected_parser = "( echo a && ( echo b || echo c ) )",
		.expected_ast =
			"SUBSHELL\n"
			"└── AND\n"
			"    ├── CMD\n"
			"    │   ├── echo\n"
			"    │   └── a\n"
			"    └── SUBSHELL\n"
			"        └── OR\n"
			"            ├── CMD\n"
			"            │   ├── echo\n"
			"            │   └── b\n"
			"            └── CMD\n"
			"                ├── echo\n"
			"                └── c"
	}
};

const t_test_block paren_block = {
	.block_name = "PAREN () TESTS",
	.block_label = "paren ()",
	.cases = paren_tests,
	.count = sizeof(paren_tests) / sizeof(paren_tests[0])
};
