/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:06:07 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/13 00:09:48 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"
#include "lexer.h" // потом подключим, когда напишем
#include <stdio.h>
#include <string.h>

static void	test_case(const char *input, const char *expected[])
{
	t_token *tokens = lexer((char *)input);
	int i = 0;

	printf("Test: \"%s\"\n", input);
	while (tokens && expected[i])
	{
		if (!tokens || strcmp(tokens->value, expected[i]) != 0)
			printf("❌ Fail: expected \"%s\", got \"%s\"\n", expected[i], tokens ? tokens->value : "(null)");
		else
			printf("✅ Ok: \"%s\"\n", expected[i]);
		tokens = tokens->next;
		i++;
	}
	if (tokens || expected[i])
		printf("❌ Fail: token count mismatch\n");
	printf("\n");
}

void	run_lexer_tests(void)
{
	const char *test1[] = {"echo", "hello", NULL};
	test_case("echo hello", test1);

	// сюда будем добавлять новые тесты
}
