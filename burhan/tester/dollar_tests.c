/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_tests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 07:17:31 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/14 07:18:49 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// dollar_block.c

#include "tester.h"

const t_test_case dollar_tests[] =
{
	// Простые случаи
	{ "echo $USER", "WORD -> 'echo', WORD -> '$USER'", "[CMD] echo $USER" },
	{ "echo $?", "WORD -> 'echo', WORD -> '$?'", "[CMD] echo $?" },
	{ "echo $1", "WORD -> 'echo', WORD -> '$1'", "[CMD] echo $1" },
	{ "echo $$", "WORD -> 'echo', WORD -> '$$'", "[CMD] echo $$" },
	{ "echo $@", "WORD -> 'echo', WORD -> '$@'", "[CMD] echo $@" },
	{ "echo $*", "WORD -> 'echo', WORD -> '$*'", "[CMD] echo $*" },

	// Пустой доллар
	{ "echo $", "WORD -> 'echo', WORD -> '$'", "[CMD] echo $" },
	{ "echo $ ", "WORD -> 'echo', WORD -> '$'", "[CMD] echo $" },

	// Несколько подряд
	{ "echo $VAR$VAR2", "WORD -> 'echo', WORD -> '$VAR$VAR2'", "[CMD] echo $VAR$VAR2" },
	{ "echo $VAR_$VAR2", "WORD -> 'echo', WORD -> '$VAR_$VAR2'", "[CMD] echo $VAR_$VAR2" },

	// С фигурными скобками
	{ "echo ${USER}", "WORD -> 'echo', WORD -> '${USER}'", "[CMD] echo ${USER}" },
	{ "echo ${}", "WORD -> 'echo', WORD -> '${}'", "[CMD] echo ${}" },
	{ "echo ${USER$ID}", "WORD -> 'echo', WORD -> '${USER$ID}'", "[CMD] echo ${USER$ID}" },

	// В кавычках
	{ "echo '$USER'", "WORD -> 'echo', WORD (quoted=SINGLE) -> '$USER'", "[CMD] echo '$USER'" },
	{ "echo \"$USER\"", "WORD -> 'echo', WORD (quoted=DOUBLE, expanded) -> '$USER'", "[CMD] echo \"$USER\"" },
	{ "echo \"$USER$HOME\"", "WORD -> 'echo', WORD (quoted=DOUBLE, expanded) -> '$USER$HOME'", "[CMD] echo \"$USER$HOME\"" },
	{ "echo '$USER$HOME'", "WORD -> 'echo', WORD (quoted=SINGLE) -> '$USER$HOME'", "[CMD] echo '$USER$HOME'" },

	// Экранирование
	{ "echo \\$USER", "WORD -> 'echo', WORD -> '$USER'", "[CMD] echo $USER" },
	{ "echo \\$?", "WORD -> 'echo', WORD -> '$?'", "[CMD] echo $?" },

	// Комбинированные кейсы
	{ "echo \"Path: $PATH\"", "WORD -> 'echo', WORD (quoted=DOUBLE, expanded) -> 'Path: $PATH'", "[CMD] echo \"Path: $PATH\"" },
	{ "echo 'Path: $PATH'", "WORD -> 'echo', WORD (quoted=SINGLE) -> 'Path: $PATH'", "[CMD] echo 'Path: $PATH'" },
	{ "echo ${UNFINISHED", "WORD -> 'echo', WORD -> '${UNFINISHED'", "[CMD] echo ${UNFINISHED" },
	{ "echo $123abc", "WORD -> 'echo', WORD -> '$123abc'", "[CMD] echo $123abc" },

	// Изолированные доллары
	{ "$", "WORD -> '$'", "[CMD] $" },
	{ "$$", "WORD -> '$$'", "[CMD] $$" },
	{ "$?", "WORD -> '$?'", "[CMD] $?" },
};

const t_test_block dollar_block = {
	.block_name = "DOLLAR EXPANSION TESTS",
	.cases = dollar_tests,
	.count = sizeof(dollar_tests) / sizeof(dollar_tests[0])
};
