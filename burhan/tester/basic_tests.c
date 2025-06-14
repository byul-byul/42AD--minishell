/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:25:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/14 15:00:14 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

const t_test_case basic_tests[] =
{
	// SIMPLE COMMANDS
	{ "ls", "WORD -> 'ls'", "[CMD] ls" },
	{ "pwd", "WORD -> 'pwd'", "[CMD] pwd" },
	{ "whoami", "WORD -> 'whoami'", "[CMD] whoami" },
	{ "clear", "WORD -> 'clear'", "[CMD] clear" },

	// WITH ARGUMENTS
	{ "ls -la", "WORD -> 'ls', WORD -> '-la'", "[CMD] ls -la" },
	{ "echo test", "WORD -> 'echo', WORD -> 'test'", "[CMD] echo test" },
	{ "mkdir new_folder", "WORD -> 'mkdir', WORD -> 'new_folder'", "[CMD] mkdir new_folder" },
	{ "rm -rf tmp", "WORD -> 'rm', WORD -> '-rf', WORD -> 'tmp'", "[CMD] rm -rf tmp" },
	{ "touch a b c", "WORD -> 'touch', WORD -> 'a', WORD -> 'b', WORD -> 'c'", "[CMD] touch a b c" },

	// BASIC OPERATORS (but no logic yet)
	{ "!", "WORD -> '!'", "[CMD] !" },
	{ "true", "WORD -> 'true'", "[CMD] true" },
	{ "false", "WORD -> 'false'", "[CMD] false" },

	// MULTIPLE SPACES / FORMATTING
	{ "   ls     -la   ", "WORD -> 'ls', WORD -> '-la'", "[CMD] ls -la" },
	{ "     echo     42     ", "WORD -> 'echo', WORD -> '42'", "[CMD] echo 42" },
	{ "\techo\t42", "WORD -> 'echo', WORD -> '42'", "[CMD] echo 42" },
	{ "   pwd", "WORD -> 'pwd'", "[CMD] pwd" },
	{ "whoami   ", "WORD -> 'whoami'", "[CMD] whoami" },

	// EDGE / BASIC SYMBOLS (not logic/pipes, just plain text)
	{ ";", "WORD -> ';'", "[CMD] ;" },
	{ ".", "WORD -> '.'", "[CMD] ." },
	{ "..", "WORD -> '..'", "[CMD] .." },
	{ ":", "WORD -> ':'", "[CMD] :" },
	{ "ls;", "WORD -> 'ls;'", "[CMD] ls;" },

	// EMPTY & NULL
	{ "", "", "[EMPTY]" },
	{ "   ", "", "[EMPTY]" }
};

const t_test_block basic_block = {
	.block_name = "BASIC TOKEN TESTS",
	.cases = basic_tests,
	.count = sizeof(basic_tests) / sizeof(basic_tests[0])
};

