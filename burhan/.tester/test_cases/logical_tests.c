/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:25:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 11:36:21 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

const t_test_case logical_tests[] =
{
	// LOGICAL_OPS CASES
	{
		.input = "cmd1 | cmd2",
		.expected_lexer = "WORD -> 'cmd1', PIPE -> '|', WORD -> 'cmd2'",
		.expected_parser = "[CMD] cmd1 | cmd2"
	},
	{
		.input = "cmd1||cmd2",
		.expected_lexer = "WORD -> 'cmd1', OR -> '||', WORD -> 'cmd2'",
		.expected_parser = "[CMD] cmd1 || cmd2"
	},
	{
		.input = "cmd1&&cmd2",
		.expected_lexer = "WORD -> 'cmd1', AND -> '&&', WORD -> 'cmd2'",
		.expected_parser = "[CMD] cmd1 && cmd2"
	},
	{
		.input = "||",
		.expected_lexer = "OR -> '||'",
		.expected_parser = "[CMD] ||"
	},
	{
		.input = "| |",
		.expected_lexer = "PIPE -> '|', PIPE -> '|'",
		.expected_parser = "[CMD] | |"
	},
	{
		.input = "|||",
		.expected_lexer = "OR -> '||', PIPE -> '|'",
		.expected_parser = "NULL"
	},
	{
		.input = "&&||",
		.expected_lexer = "AND -> '&&', OR -> '||'",
		.expected_parser = "[CMD] && ||"
	},
	{
		.input = "cmd &&",
		.expected_lexer = "WORD -> 'cmd', AND -> '&&'",
		.expected_parser = "[CMD] cmd &&"
	},
	{
		.input = "cmd ||",
		.expected_lexer = "WORD -> 'cmd', OR -> '||'",
		.expected_parser = "[CMD] cmd ||"
	},
	{
		.input = "cmd1&&",
		.expected_lexer = "WORD -> 'cmd1', AND -> '&&'",
		.expected_parser = "[CMD] cmd1 &&"
	},
	{
		.input = "cmd1||",
		.expected_lexer = "WORD -> 'cmd1', OR -> '||'",
		.expected_parser = "[CMD] cmd1 ||"
	},
	// LOGICAL_OPS — EXTENDED
	{
		.input = "echo hello && ls || echo fail",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello', AND -> '&&', WORD -> 'ls', OR -> '||', WORD -> 'echo', WORD -> 'fail'",
		.expected_parser = "[CMD] echo hello && ls || echo fail"
	},
	{
		.input = "&&cmd",
		.expected_lexer = "AND -> '&&', WORD -> 'cmd'",
		.expected_parser = "[CMD] && cmd"
	},
	{
		.input = "\"||\"",
		.expected_lexer = "WORD -> '||'",
		.expected_parser = "[CMD] \"||\""
	},
	{
		.input = "echo hi ||\nls",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hi', OR -> '||', WORD -> 'ls'",
		.expected_parser = "[CMD] echo hi || ls"
	},
	{
		.input = "|||cmd",
		.expected_lexer = "OR -> '||', PIPE -> '|', WORD -> 'cmd'",
		.expected_parser = "[CMD] | || cmd"
	}
};

const t_test_block logical_block = {
	.block_name = "LOGICAL TESTS",
	.block_label = "logical",
	.cases = logical_tests,
	.count = sizeof(logical_tests) / sizeof(logical_tests[0])
};
