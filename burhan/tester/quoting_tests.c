/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:26:13 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/15 21:34:38 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

const t_test_case quoting_tests[] =
{
	// QUOTING CASES
	{
		.input = "echo 'hello world'",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello world'",
		.expected_parser = "[CMD] echo 'hello world'"
	},
	{
		.input = "echo \"hello world\"",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello world'",
		.expected_parser = "[CMD] echo \"hello world\""
	},
	{
		.input = "echo 'a\"b'",
		.expected_lexer = "WORD -> 'echo', WORD -> 'a\"b'",
		.expected_parser = "[CMD] echo 'a\"b'"
	},
	{
		.input = "echo \"a'b\"",
		.expected_lexer = "WORD -> 'echo', WORD -> 'a'b'",
		.expected_parser = "[CMD] echo \"a'b\""
	},
	{
		.input = "echo 'a b' c",
		.expected_lexer = "WORD -> 'echo', WORD -> 'a b', WORD -> 'c'",
		.expected_parser = "[CMD] echo 'a b' c"
	},
	{
		.input = "echo \"a b\" c",
		.expected_lexer = "WORD -> 'echo', WORD -> 'a b', WORD -> 'c'",
		.expected_parser = "[CMD] echo \"a b\" c"
	},
	{
		.input = "echo 'a\"b'\"c\"",
		.expected_lexer = "WORD -> 'echo', WORD -> 'a\"bc'",
		.expected_parser = "[CMD] echo 'a\"b'\"c\""
	},
	{
		.input = "echo ''",
		.expected_lexer = "WORD -> 'echo', WORD -> ''",
		.expected_parser = "[CMD] echo ''"
	},
	{
		.input = "echo \"\"",
		.expected_lexer = "WORD -> 'echo', WORD -> ''",
		.expected_parser = "[CMD] echo \"\""
	},
	{
		.input = "echo 'a $b'",
		.expected_lexer = "WORD -> 'echo', WORD -> 'a $b'",
		.expected_parser = "[CMD] echo 'a $b'"
	},
	{
		.input = "echo \"a $b\"",
		.expected_lexer = "WORD -> 'echo', WORD -> 'a $b'",
		.expected_parser = "[CMD] echo \"a $b\""
	},
	{
		.input = "echo \"text with \\\"escaped quotes\\\" inside\"",
		.expected_lexer = "WORD -> 'echo', WORD -> 'text with \"escaped quotes\" inside'",
		.expected_parser = "[CMD] echo \"text with \\\"escaped quotes\\\" inside\""
	},
	{
		.input = "'\"$USER\"'",
		.expected_lexer = "WORD -> '\"$USER\"'",
		.expected_parser = "[CMD] '\"$USER\"'"
	},
	{
		.input = "\"'\"'$USER'",
		.expected_lexer = "WORD -> ''$USER'",
		.expected_parser = "[CMD] \"'\"'$USER'"
	},
	{
		.input = "''",
		.expected_lexer = "WORD -> ''",
		.expected_parser = "[CMD] ''"
	},
	{
		.input = "\"\"",
		.expected_lexer = "WORD -> ''",
		.expected_parser = "[CMD] \"\""
	},
	{
		.input = "' '",
		.expected_lexer = "WORD -> ' '",
		.expected_parser = "[CMD] ' '"
	},
	{
		.input = "\" \"",
		.expected_lexer = "WORD -> ' '",
		.expected_parser = "[CMD] \" \""
	}

};

const t_test_block quoting_block = {
	.block_name = "QUOTING TESTS",
	.block_label = "quoting",
	.cases = quoting_tests,
	.count = sizeof(quoting_tests) / sizeof(quoting_tests[0])
};
