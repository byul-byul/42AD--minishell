/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_quoting_tests.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:54:18 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/23 22:10:47 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

const t_test_case invalid_quotes_tests[] =
{
	{
		.input = "\"unclosed double",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "'unclosed single",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "\"mixed 'quotes\"",
		.expected_lexer = "WORD -> 'mixed 'quotes'",
		.expected_parser = "NULL"
	},
	{
		.input = "'nested \"quotes",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "'$VAR",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "\"$VAR",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "\"a'$b\"c",
		.expected_lexer = "WORD -> 'a'$bc'",
		.expected_parser = "NULL"
	},
	{
		.input = "\"abc",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "'abc",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "\"",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "'",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "echo 'unterminated",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	},
	{
		.input = "echo \"unterminated",
		.expected_lexer = "NULL",
		.expected_parser = "NULL"
	}
};

const t_test_block invalid_quotting_block = {
	.block_name = "INVALID QUOTING TESTS",
	.block_label = "invalid quoting",
	.cases = invalid_quotes_tests,
	.count = sizeof(invalid_quotes_tests) / sizeof(invalid_quotes_tests[0])
};
