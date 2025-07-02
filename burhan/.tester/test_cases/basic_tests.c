/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:25:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 03:15:56 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

const t_test_case basic_tests[] =
{
	// SIMPLE COMMANDS
	{
		.input = "ls",
		.expected_lexer = "WORD -> 'ls'",
		.expected_expander = "WORD -> 'ls'",
		.expected_parser = "ls",
		.expected_ast =
			"CMD\n"
			"└── ls"
	},
	{
		.input = "pwd",
		.expected_lexer = "WORD -> 'pwd'",
		.expected_expander = "WORD -> 'pwd'",
		.expected_parser = "pwd",
		.expected_ast =
			"CMD\n"
			"└── pwd"
	},
	{
		.input = "whoami",
		.expected_lexer = "WORD -> 'whoami'",
		.expected_expander = "WORD -> 'whoami'",
		.expected_parser = "whoami",
		.expected_ast =
			"CMD\n"
			"└── whoami"
	},
	{
		.input = "clear",
		.expected_lexer = "WORD -> 'clear'",
		.expected_expander = "WORD -> 'clear'",
		.expected_parser = "clear",
		.expected_ast =
			"CMD\n"
			"└── clear"
	},

	// WITH ARGUMENTS
	{
		.input = "ls -la",
		.expected_lexer = "WORD -> 'ls', WORD -> '-la'",
		.expected_expander = "WORD -> 'ls', WORD -> '-la'",
		.expected_parser = "ls -la",
		.expected_ast =
			"CMD\n"
			"├── ls\n"
			"└── -la"
	},
	{
		.input = "echo test",
		.expected_lexer = "WORD -> 'echo', WORD -> 'test'",
		.expected_expander = "WORD -> 'echo', WORD -> 'test'",
		.expected_parser = "echo test",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── test"
	},
	{
		.input = "mkdir new_folder",
		.expected_lexer = "WORD -> 'mkdir', WORD -> 'new_folder'",
		.expected_expander = "WORD -> 'mkdir', WORD -> 'new_folder'",
		.expected_parser = "mkdir new_folder",
		.expected_ast =
			"CMD\n"
			"├── mkdir\n"
			"└── new_folder"
	},
	{
		.input = "rm -rf tmp",
		.expected_lexer = "WORD -> 'rm', WORD -> '-rf', WORD -> 'tmp'",
		.expected_expander = "WORD -> 'rm', WORD -> '-rf', WORD -> 'tmp'",
		.expected_parser = "rm -rf tmp",
		.expected_ast =
			"CMD\n"
			"├── rm\n"
			"├── -rf\n"
			"└── tmp"
	},
	{
		.input = "touch a b c",
		.expected_lexer = "WORD -> 'touch', WORD -> 'a', WORD -> 'b', WORD -> 'c'",
		.expected_expander = "WORD -> 'touch', WORD -> 'a', WORD -> 'b', WORD -> 'c'",
		.expected_parser = "touch a b c",
		.expected_ast =
			"CMD\n"
			"├── touch\n"
			"├── a\n"
			"├── b\n"
			"└── c"
	},

	// BASIC OPERATORS
	{
		.input = "!",
		.expected_lexer = "WORD -> '!'",
		.expected_expander = "WORD -> '!'",
		.expected_parser = "!",
		.expected_ast =
			"CMD\n"
			"└── !"
	},
	{
		.input = "true",
		.expected_lexer = "WORD -> 'true'",
		.expected_expander = "WORD -> 'true'",
		.expected_parser = "true",
		.expected_ast =
			"CMD\n"
			"└── true"
	},
	{
		.input = "false",
		.expected_lexer = "WORD -> 'false'",
		.expected_expander = "WORD -> 'false'",
		.expected_parser = "false",
		.expected_ast =
			"CMD\n"
			"└── false"
	},

	// MULTIPLE SPACES
	{
		.input = "   ls     -la   ",
		.expected_lexer = "WORD -> 'ls', WORD -> '-la'",
		.expected_expander = "WORD -> 'ls', WORD -> '-la'",
		.expected_parser = "ls -la",
		.expected_ast =
			"CMD\n"
			"├── ls\n"
			"└── -la"
	},
	{
		.input = "     echo     42     ",
		.expected_lexer = "WORD -> 'echo', WORD -> '42'",
		.expected_expander = "WORD -> 'echo', WORD -> '42'",
		.expected_parser = "echo 42",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── 42"
	},
	{
		.input = "\techo\t42",
		.expected_lexer = "WORD -> 'echo', WORD -> '42'",
		.expected_expander = "WORD -> 'echo', WORD -> '42'",
		.expected_parser = "echo 42",
		.expected_ast =
			"CMD\n"
			"├── echo\n"
			"└── 42"
	},
	{
		.input = "   pwd",
		.expected_lexer = "WORD -> 'pwd'",
		.expected_expander = "WORD -> 'pwd'",
		.expected_parser = "pwd",
		.expected_ast =
			"CMD\n"
			"└── pwd"
	},
	{
		.input = "whoami   ",
		.expected_lexer = "WORD -> 'whoami'",
		.expected_expander = "WORD -> 'whoami'",
		.expected_parser = "whoami",
		.expected_ast =
			"CMD\n"
			"└── whoami"
	},

	// BASIC SYMBOLS
	{
		.input = ";",
		.expected_lexer = "WORD -> ';'",
		.expected_expander = "WORD -> ';'",
		.expected_parser = ";",
		.expected_ast =
			"CMD\n"
			"└── ;"
	},
	{
		.input = ".",
		.expected_lexer = "WORD -> '.'",
		.expected_expander = "WORD -> '.'",
		.expected_parser = ".",
		.expected_ast =
			"CMD\n"
			"└── ."
	},
	{
		.input = "..",
		.expected_lexer = "WORD -> '..'",
		.expected_expander = "WORD -> '..'",
		.expected_parser = "..",
		.expected_ast =
			"CMD\n"
			"└── .."
	},
	{
		.input = ":",
		.expected_lexer = "WORD -> ':'",
		.expected_expander = "WORD -> ':'",
		.expected_parser = ":",
		.expected_ast =
			"CMD\n"
			"└── :"
	},
	{
		.input = "ls;",
		.expected_lexer = "WORD -> 'ls;'",
		.expected_expander = "WORD -> 'ls;'",
		.expected_parser = "ls;",
		.expected_ast =
			"CMD\n"
			"└── ls;"
	},

	// EMPTY & NULL
	{
		.input = "",
		.expected_lexer = "NULL",
		.expected_expander = "",
		.expected_parser = "NULL",
		.expected_ast = "[EMPTY]"
	},
	{
		.input = "   ",
		.expected_lexer = "NULL",
		.expected_expander = "",
		.expected_parser = "NULL",
		.expected_ast = "[EMPTY]"
	},
	{
	.input = "echo \"\"",
	.expected_lexer = "WORD -> 'echo', WORD -> ''",
	.expected_expander = "WORD -> 'echo', WORD -> ''",
	.expected_parser = "echo \"\"",
	.expected_ast =
		"CMD\n"
		"├── echo\n"
		"└── "
	},
	{
		.input = "ls \"\"",
		.expected_lexer = "WORD -> 'ls', WORD -> ''",
		.expected_expander = "WORD -> 'ls', WORD -> ''",
		.expected_parser = "ls \"\"",
		.expected_ast =
			"CMD\n"
			"├── ls\n"
			"└── "
	},
	{
		.input = "ls a \"\" b",
		.expected_lexer = "WORD -> 'ls', WORD -> 'a', WORD -> '', WORD -> 'b'",
		.expected_expander = "WORD -> 'ls', WORD -> 'a', WORD -> '', WORD -> 'b'",
		.expected_parser = "ls a \"\" b",
		.expected_ast =
			"CMD\n"
			"├── ls\n"
			"├── a\n"
			"├── \n"
			"└── b"
	},
	{
		.input = "true false",
		.expected_lexer = "WORD -> 'true', WORD -> 'false'",
		.expected_expander = "WORD -> 'true', WORD -> 'false'",
		.expected_parser = "true false",
		.expected_ast =
			"CMD\n"
			"├── true\n"
			"└── false"
	},
	{
		.input = "a;b;c",
		.expected_lexer = "WORD -> 'a;b;c'",
		.expected_expander = "WORD -> 'a;b;c'",
		.expected_parser = "a;b;c",
		.expected_ast =
			"CMD\n"
			"└── a;b;c"
	}

};

const t_test_block basic_block = {
	.block_name = "BASIC TESTS",
	.block_label = "basic",
	.cases = basic_tests,
	.count = sizeof(basic_tests) / sizeof(basic_tests[0])
};
