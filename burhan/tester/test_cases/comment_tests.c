/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comment_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:25:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 12:57:29 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

const t_test_case comment_tests[] =
{
	{
		.input = "cmd1 || # comment",
		.expected_lexer = "WORD -> 'cmd1', OR -> '||'",
		.expected_parser = "[CMD] cmd1 ||"
	},
	{
		.input = "# this is a comment",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "   # comment after spaces",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "echo hello # comment",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello'",
		.expected_parser = "[CMD] echo hello"
	},
	{
		.input = "echo #comment",
		.expected_lexer = "WORD -> 'echo'",
		.expected_parser = "[CMD] echo"
	},
	{
		.input = "echo \"#notcomment\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '#notcomment'",
		.expected_parser = "[CMD] echo #notcomment"
	},
	{
		.input = "echo '#still not comment'",
		.expected_lexer = "WORD -> 'echo', WORD -> '#still not comment'",
		.expected_parser = "[CMD] echo #still not comment"
	},
	{
		.input = "echo hello#notcomment",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello#notcomment'",
		.expected_parser = "[CMD] echo hello#notcomment"
	},
	{
		.input = "echo hello#not comment",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello#not', WORD -> 'comment'",
		.expected_parser = "[CMD] echo hello#not"
	},
	{
		.input = "echo 'abc # def'",
		.expected_lexer = "WORD -> 'echo', WORD -> 'abc # def'",
		.expected_parser = "[CMD] echo abc # def"
	},
	{
		.input = "echo \"abc # def\"",
		.expected_lexer = "WORD -> 'echo', WORD -> 'abc # def'",
		.expected_parser = "[CMD] echo abc # def"
	},
};

const t_test_block comment_block = {
	.block_name = "COMMENT # TESTS",
	.block_label = "comment #",
	.cases = comment_tests,
	.count = sizeof(comment_tests) / sizeof(comment_tests[0])
};
