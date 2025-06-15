/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tester.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:06:07 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/15 15:52:21 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../incls/expander.h"
#include "tester.h"

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

int g_test_num = 1;
int g_failed_tests[1024];
int g_failed_count = 0;

static const char *get_type_name(t_token_type type)
{
	return (
		type == WORD ? "WORD" :
		type == PIPE ? "PIPE" :
		type == REDIR_IN ? "REDIR_IN" :
		type == REDIR_OUT ? "REDIR_OUT" :
		type == HEREDOC ? "HEREDOC" :
		type == APPEND ? "APPEND" :
		type == LOGICAL_AND ? "AND" :
		type == LOGICAL_OR ? "OR" :
		type == OPEN_PAREN ? "OPEN_PAREN" :
		type == CLOSE_PAREN ? "CLOSE_PAREN" : "UNKNOWN"
	);
}

void	print_tokens_verbose(t_token *tokens)
{
	while (tokens)
	{
		printf("value: %-16s | type: %-13s | quoted: %d | heredoc_expand: %d | expanded: %d\n",
			tokens->value,
			get_type_name(tokens->type),
			tokens->quoted,
			tokens->heredoc_expand,
			tokens->expanded);
		tokens = tokens->next;
	}
}

void	run_test(const char *input, const char *expected_expander, const char *block_label)
{
	t_token	*tokens = lexer((char *)input);
	char	actual[2048] = "";
	char	tmp_buf[512];

	printf(BLUE "Expander test_%d (%s) " RESET, g_test_num, block_label);
	// printf(BLUE "==== INPUT: \"%s\" ====\n" RESET, input);
	// printf(YELLOW "Expected: %s\n" RESET, expected_expander);

	if (!tokens)
	{
		if (strcmp(expected_expander, "") == 0 || strcmp(expected_expander, "NULL") == 0)
		{
			// printf(GREEN "Actual  : NULL\n" RESET);
			printf(GREEN "✅ Ok\n" RESET);
		}
		else
		{
			printf(BLUE "==== INPUT: \"%s\" ====\n" RESET, input);
			printf(YELLOW "Expected: %s\n" RESET, expected_expander);
			printf(RED "Actual  : NULL\n" RESET);
			printf(RED "❌ FAIL\n\n" RESET);
			g_failed_tests[g_failed_count++] = g_test_num;
		}
		g_test_num++;
		return;
	}

	expander(tokens, 0);

	t_token *tmp = tokens;
	while (tmp)
	{
		sprintf(tmp_buf, "%s -> '%s'", get_type_name(tmp->type), tmp->value);
		strcat(actual, tmp_buf);
		if (tmp->next)
			strcat(actual, ", ");
		tmp = tmp->next;
	}

	if (strcmp(actual, expected_expander) == 0)
	{
		// printf(GREEN "Actual  : %s\n" RESET, actual);
		// print_tokens_verbose(tokens);
		printf(GREEN "✅ Ok\n" RESET);
	}
	else
	{
		printf(BLUE "==== INPUT: \"%s\" ====\n" RESET, input);
		printf(YELLOW "Expected: %s\n" RESET, expected_expander);
		printf(RED "Actual  : %s\n" RESET, actual);
		print_tokens_verbose(tokens);
		printf(RED "❌ FAIL\n\n" RESET);
		g_failed_tests[g_failed_count++] = g_test_num;
	}

	clean_token_list(tokens);
	g_test_num++;
}

void	run_block(const t_test_block *block)
{
	printf(CYAN "\n=== %s ===\n" RESET, block->block_name);
	for (int i = 0; i < block->count; i++)
		run_test(block->cases[i].input, block->cases[i].expected_expander, block->block_label);
	printf(CYAN "=== END OF %s ===\n" RESET, block->block_name);
}

void	report_failed_tests(void)
{
	if (g_failed_count == 0)
	{
		printf(GREEN "\nAll tests passed!\n" RESET);
		return;
	}
	printf(RED "\n❌ Failed test cases:\n" RESET);
	for (int i = 0; i < g_failed_count; i++)
		printf(RED "❌ test_%d\n" RESET, g_failed_tests[i]);
}

// Declare your test blocks here
extern const t_test_block basic_block;
extern const t_test_block dollar_block;
extern const t_test_block quoting_block;
extern const t_test_block invalid_quotting_block;
extern const t_test_block redirection_block;

int	main(void)
{
	run_block(&basic_block);
	// run_block(&dollar_block);
	// run_block(&quoting_block);
	// run_block(&invalid_quotting_block);
	// run_block(&redirection_block);
	report_failed_tests();
	return (0);
}
