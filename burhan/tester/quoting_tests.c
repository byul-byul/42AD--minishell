/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quoting_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 16:26:13 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/14 16:26:24 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

const t_test_case quoting_tests[] =
{
	{ "echo 'hello world'", "WORD -> 'echo', WORD -> 'hello world'", "[CMD] echo 'hello world'" },
	{ "echo \"hello world\"", "WORD -> 'echo', WORD -> 'hello world'", "[CMD] echo \"hello world\"" },
	{ "echo 'a\"b'", "WORD -> 'echo', WORD -> 'a\"b'", "[CMD] echo 'a\"b'" },
	{ "echo \"a'b\"", "WORD -> 'echo', WORD -> 'a'b'", "[CMD] echo \"a'b\"" },
	{ "echo 'a b' c", "WORD -> 'echo', WORD -> 'a b', WORD -> 'c'", "[CMD] echo 'a b' c" },
	{ "echo \"a b\" c", "WORD -> 'echo', WORD -> 'a b', WORD -> 'c'", "[CMD] echo \"a b\" c" },
	{ "echo 'a\"b'\"c\"", "WORD -> 'echo', WORD -> 'a\"bc'", "[CMD] echo 'a\"b'\"c\"" },
	{ "echo 'unterminated", "NULL", "NULL" },
	{ "echo \"unterminated", "NULL", "NULL" },
	{ "echo ''", "WORD -> 'echo', WORD -> ''", "[CMD] echo ''" },
	{ "echo \"\"", "WORD -> 'echo', WORD -> ''", "[CMD] echo \"\"" },
	{ "echo 'a $b'", "WORD -> 'echo', WORD -> 'a $b'", "[CMD] echo 'a $b'" },
	{ "echo \"a $b\"", "WORD -> 'echo', WORD -> 'a $b'", "[CMD] echo \"a $b\"" },
	{ "echo \"text with \\\"escaped quotes\\\" inside\"", "WORD -> 'echo', WORD -> 'text with \"escaped quotes\" inside'", "[CMD] echo ..." },
	{ "'\"$USER\"'", "WORD -> '\"$USER\"'", "[CMD] '\"$USER\"'" },
	{ "\"'\"'$USER'", "WORD -> \"''$USER\"", "[CMD] \"'\"'$USER'" },
	{ "''", "WORD -> ''", "[CMD] ''" },
	{ "\"\"", "WORD -> ''", "[CMD] \"\"" },
	{ "' '", "WORD -> ' '", "[CMD] ' '" },
	{ "\" \"", "WORD -> ' '", "[CMD] \" \"" }
};

const t_test_block quoting_block = {
	.block_name = "QUOTING TESTS",
	.cases = quoting_tests,
	.count = sizeof(quoting_tests) / sizeof(quoting_tests[0])
};
