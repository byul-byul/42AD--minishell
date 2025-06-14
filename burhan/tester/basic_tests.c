/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:25:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/14 21:00:52 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

const t_test_case basic_tests[] =
{
	// SIMPLE COMMANDS
	{
		.input = "ls",
		.expected_lexer = "WORD -> 'ls'",
		.expected_parser = "[CMD] ls"
	},
	{
		.input = "pwd",
		.expected_lexer = "WORD -> 'pwd'",
		.expected_parser = "[CMD] pwd"
	},
	{
		.input = "whoami",
		.expected_lexer = "WORD -> 'whoami'",
		.expected_parser = "[CMD] whoami"
	},
	{
		.input = "clear",
		.expected_lexer = "WORD -> 'clear'",
		.expected_parser = "[CMD] clear"
	},

	// WITH ARGUMENTS
	{
		.input = "ls -la",
		.expected_lexer = "WORD -> 'ls', WORD -> '-la'",
		.expected_parser = "[CMD] ls -la"
	},
	{
		.input = "echo test",
		.expected_lexer = "WORD -> 'echo', WORD -> 'test'",
		.expected_parser = "[CMD] echo test"
	},
	{
		.input = "mkdir new_folder",
		.expected_lexer = "WORD -> 'mkdir', WORD -> 'new_folder'",
		.expected_parser = "[CMD] mkdir new_folder"
	},
	{
		.input = "rm -rf tmp",
		.expected_lexer = "WORD -> 'rm', WORD -> '-rf', WORD -> 'tmp'",
		.expected_parser = "[CMD] rm -rf tmp"
	},
	{
		.input = "touch a b c",
		.expected_lexer = "WORD -> 'touch', WORD -> 'a', WORD -> 'b', WORD -> 'c'",
		.expected_parser = "[CMD] touch a b c"
	},

	// BASIC OPERATORS (but no logic yet)
	{
		.input = "!",
		.expected_lexer = "WORD -> '!'",
		.expected_parser = "[CMD] !"
	},
	{
		.input = "true",
		.expected_lexer = "WORD -> 'true'",
		.expected_parser = "[CMD] true"
	},
	{
		.input = "false",
		.expected_lexer = "WORD -> 'false'",
		.expected_parser = "[CMD] false"
	},

	// MULTIPLE SPACES / FORMATTING
	{
		.input = "   ls     -la   ",
		.expected_lexer = "WORD -> 'ls', WORD -> '-la'",
		.expected_parser = "[CMD] ls -la"
	},
	{
		.input = "     echo     42     ",
		.expected_lexer = "WORD -> 'echo', WORD -> '42'",
		.expected_parser = "[CMD] echo 42"
	},
	{
		.input = "\techo\t42",
		.expected_lexer = "WORD -> 'echo', WORD -> '42'",
		.expected_parser = "[CMD] echo 42"
	},
	{
		.input = "   pwd",
		.expected_lexer = "WORD -> 'pwd'",
		.expected_parser = "[CMD] pwd"
	},
	{
		.input = "whoami   ",
		.expected_lexer = "WORD -> 'whoami'",
		.expected_parser = "[CMD] whoami"
	},

	// EDGE / BASIC SYMBOLS (not logic/pipes, just plain text)
	{
		.input = ";",
		.expected_lexer = "WORD -> ';'",
		.expected_parser = "[CMD] ;"
	},
	{
		.input = ".",
		.expected_lexer = "WORD -> '.'",
		.expected_parser = "[CMD] ."
	},
	{
		.input = "..",
		.expected_lexer = "WORD -> '..'",
		.expected_parser = "[CMD] .."
	},
	{
		.input = ":",
		.expected_lexer = "WORD -> ':'",
		.expected_parser = "[CMD] :"
	},
	{
		.input = "ls;",
		.expected_lexer = "WORD -> 'ls;'",
		.expected_parser = "[CMD] ls;"
	},

	// EMPTY & NULL
	{
		.input = "",
		.expected_lexer = "",
		.expected_parser = "[EMPTY]"
	},
	{
		.input = "   ",
		.expected_lexer = "",
		.expected_parser = "[EMPTY]"
	}
};

const t_test_block basic_block = {
	.block_name = "BASIC TOKEN TESTS",
	.block_label = "basic",
	.cases = basic_tests,
	.count = sizeof(basic_tests) / sizeof(basic_tests[0])
};

