/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   escape_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:25:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 15:20:04 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

const t_test_case escape_tests[] =
{
	// ESCAPE SEQUENCES (Expanded)
	{
		.input = "echo \\$USER",
		.expected_lexer = "WORD -> 'echo', WORD -> '\\$USER'",
		.expected_expander = "WORD -> 'echo', WORD -> '\\byulbyul'",
		.expected_parser = "echo \\$USER",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── \\byulbyul"
	},
	{
		.input = "echo \\\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '\\\"'",
		.expected_expander = "WORD -> 'echo', WORD -> '\\\"'",
		.expected_parser = "echo \\\"",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── \\\""
	},
	{
		.input = "echo \\\\",
		.expected_lexer = "WORD -> 'echo', WORD -> '\\\\'",
		.expected_expander = "WORD -> 'echo', WORD -> '\\\\'",
		.expected_parser = "echo \\\\",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── \\\\"
	},
	{
		.input = "echo \\|\\&\\;",
		.expected_lexer = "WORD -> 'echo', WORD -> '\\|\\&\\;'",
		.expected_expander = "WORD -> 'echo', WORD -> '\\|\\&\\;'",
		.expected_parser = "echo \\|\\&\\;",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── \\|\\&\\;;"
	},
	{
		.input = "\\|",
		.expected_lexer = "WORD -> '|'",
		.expected_expander = "WORD -> '|'",
		.expected_parser = "|",
		.expected_ast =
			"CMD\n"
			"└── |"
	},
	{
		.input = "cmd\\&&",
		.expected_lexer = "WORD -> 'cmd&&'",
		.expected_expander = "WORD -> 'cmd&&'",
		.expected_parser = "cmd\\&&",
		.expected_ast =
			"CMD\n"
			"└── cmd&&"
	},
	{
		.input = "\\ ",
		.expected_lexer = "WORD -> ' '",
		.expected_expander = "WORD -> ' '",
		.expected_parser = "\\ ",
		.expected_ast =
			"CMD\n"
			"└──  "
	},
	{
		.input = "echo '\\$USER'",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER'",
		.expected_expander = "WORD -> 'echo', WORD -> '$USER'",
		.expected_parser = "echo '$USER'",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── $USER"
	},
	{
		.input = "echo \"\\$USER\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER'",
		.expected_expander = "WORD -> 'echo', WORD -> 'byulbyul'",
		.expected_parser = "echo \"$USER\"",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── byulbyul"
	},
	{
		.input = "echo \\\"'\\''\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '\"'\''\"'",
		.expected_expander = "WORD -> 'echo', WORD -> '\"'\''\"'",
		.expected_parser = "echo \\\"'\\''\"",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── \"'\''\""
	},
	{
		.input = "echo a\\ b\\ c",
		.expected_lexer = "WORD -> 'echo', WORD -> 'a\\', WORD -> 'b\\', WORD -> 'c'",
		.expected_expander = "WORD -> 'echo', WORD -> 'a\\', WORD -> 'b\\', WORD -> 'c'",
		.expected_parser = "echo a\\ b\\ c",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── a\\\n"
			"└── b\\\n"
			"└── c"
	},
	{
		.input = "echo \\#notacomment",
		.expected_lexer = "WORD -> 'echo', WORD -> '\\#notacomment'",
		.expected_expander = "WORD -> 'echo', WORD -> '\\#notacomment'",
		.expected_parser = "echo \\#notacomment",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── \\#notacomment"
	},
	{
		.input = "echo foo\\",
		.expected_lexer = "WORD -> 'echo', WORD -> 'foo\\'",
		.expected_expander = "WORD -> 'echo', WORD -> 'foo\\'",
		.expected_parser = "echo foo\\",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── foo\\"
	}
};

const t_test_block escape_block = {
	.block_name = "ESCAPE \\ TESTS",
	.block_label = "escape \\",
	.cases = escape_tests,
	.count = sizeof(escape_tests) / sizeof(escape_tests[0])
};
