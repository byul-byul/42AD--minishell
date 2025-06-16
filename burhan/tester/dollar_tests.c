/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 07:17:31 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/16 16:02:24 by bhajili          ###   ########.fr       */
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
		.expected_parser = "[CMD] echo $USER",
		.expected_expander = "WORD -> 'echo', WORD -> 'byulbyul'" },
	{
		.input = "echo $?",
		.expected_lexer = "WORD -> 'echo', WORD -> '$?'",
		.expected_parser = "[CMD] echo $?",
		.expected_expander = "WORD -> 'echo', WORD -> '0'" },
	{
		.input = "echo $1",
		.expected_lexer = "WORD -> 'echo', WORD -> '$1'",
		.expected_parser = "[CMD] echo $1",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },
	{
		.input = "echo $$",
		.expected_lexer = "WORD -> 'echo', WORD -> '$$'",
		.expected_parser = "[CMD] echo $$",
		.expected_expander = "WORD -> 'echo', WORD -> '99999'" },
	{
		.input = "echo $@",
		.expected_lexer = "WORD -> 'echo', WORD -> '$@'",
		.expected_parser = "[CMD] echo $@",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },
	{
		.input = "echo $*",
		.expected_lexer = "WORD -> 'echo', WORD -> '$*'",
		.expected_parser = "[CMD] echo $*",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },

	// EMPTY DOLLAR
	{
		.input = "echo $",
		.expected_lexer = "WORD -> 'echo', WORD -> '$'",
		.expected_parser = "[CMD] echo $",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },
	{
		.input = "echo $ ",
		.expected_lexer = "WORD -> 'echo', WORD -> '$'",
		.expected_parser = "[CMD] echo $",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },

	// MULTIPLE VARIABLES TOGETHER
	{
		.input = "echo $VAR$VAR2",
		.expected_lexer = "WORD -> 'echo', WORD -> '$VAR$VAR2'",
		.expected_parser = "[CMD] echo $VAR$VAR2",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },
	{
		.input = "echo $VAR_$VAR2",
		.expected_lexer = "WORD -> 'echo', WORD -> '$VAR_$VAR2'",
		.expected_parser = "[CMD] echo $VAR_$VAR2",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },

	// WITH CURLY BRACES
	{
		.input = "echo ${USER}",
		.expected_lexer = "WORD -> 'echo', WORD -> '${USER}'",
		.expected_parser = "[CMD] echo ${USER}",
		.expected_expander = "WORD -> 'echo', WORD -> 'byulbyul'" },
	{
		.input = "echo ${}",
		.expected_lexer = "WORD -> 'echo', WORD -> '${}'",
		.expected_parser = "[CMD] echo ${}",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },
	{
		.input = "echo ${USER$ID}",
		.expected_lexer = "WORD -> 'echo', WORD -> '${USER$ID}'",
		.expected_parser = "[CMD] echo ${USER$ID}",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },

	// INSIDE QUOTES
	{
		.input = "echo '$USER'",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER'",
		.expected_parser = "[CMD] echo '$USER'",
		.expected_expander = "WORD -> 'echo', WORD -> '$USER'" },
	{
		.input = "echo \"$USER\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER'",
		.expected_parser = "[CMD] echo \"$USER\"",
		.expected_expander = "WORD -> 'echo', WORD -> 'byulbyul'" },
	{
		.input = "echo \"$USER$HOME\"",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER$HOME'",
		.expected_parser = "[CMD] echo \"$USER$HOME\"",
		.expected_expander = "WORD -> 'echo', WORD -> 'byulbyul/home'" },
	{
		.input = "echo '$USER$HOME'",
		.expected_lexer = "WORD -> 'echo', WORD -> '$USER$HOME'",
		.expected_parser = "[CMD] echo '$USER$HOME'",
		.expected_expander = "WORD -> 'echo', WORD -> '$USER$HOME'" },

	// ESCAPED DOLLARS
	{
		.input = "echo \\$USER",
		.expected_lexer = "WORD -> 'echo', WORD -> '\\$USER'",
		.expected_parser = "[CMD] echo $USER",
		.expected_expander = "WORD -> 'echo', WORD -> '$USER'" },
	{
		.input = "echo \\$?",
		.expected_lexer = "WORD -> 'echo', WORD -> '\\$?'",
		.expected_parser = "[CMD] echo $?",
		.expected_expander = "WORD -> 'echo', WORD -> '$?'" },

	// MIXED / COMPLEX CASES
	{
		.input = "echo \"Path: $PATH\"",
		.expected_lexer = "WORD -> 'echo', WORD -> 'Path: $PATH'",
		.expected_parser = "[CMD] echo \"Path: $PATH\"",
		.expected_expander = "WORD -> 'echo', WORD -> 'Path: /usr/bin:/bin'" },
	{
		.input = "echo 'Path: $PATH'",
		.expected_lexer = "WORD -> 'echo', WORD -> 'Path: $PATH'",
		.expected_parser = "[CMD] echo 'Path: $PATH'",
		.expected_expander = "WORD -> 'echo', WORD -> 'Path: $PATH'" },
	{
		.input = "echo ${UNFINISHED",
		.expected_lexer = "WORD -> 'echo', WORD -> '${UNFINISHED'",
		.expected_parser = "[CMD] echo ${UNFINISHED",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },
	{
		.input = "echo $123abc",
		.expected_lexer = "WORD -> 'echo', WORD -> '$123abc'",
		.expected_parser = "[CMD] echo $123abc",
		.expected_expander = "WORD -> 'echo', WORD -> ''" },

	// ISOLATED DOLLARS
	{
		.input = "$",
		.expected_lexer = "WORD -> '$'",
		.expected_parser = "[CMD] $",
		.expected_expander = "WORD -> ''" },
	{
		.input = "$$",
		.expected_lexer = "WORD -> '$$'",
		.expected_parser = "[CMD] $$",
		.expected_expander = "WORD -> '99999'" },
	{
		.input = "$?",
		.expected_lexer = "WORD -> '$?'",
		.expected_parser = "[CMD] $?",
		.expected_expander = "WORD -> '0'" }
};


const t_test_block dollar_block = {
	.block_name = "DOLLAR EXPANSION TESTS",
	.block_label = "dollar sign $",
	.cases = dollar_tests,
	.count = sizeof(dollar_tests) / sizeof(dollar_tests[0])
};
