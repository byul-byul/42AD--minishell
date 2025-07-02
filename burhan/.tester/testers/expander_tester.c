/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_tester.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:06:07 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 15:48:06 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

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
		printf("token: %-16s | type: %-13s | heredoc_expand: %d | expanded: %d | ",
			tokens->value,
			get_type_name(tokens->type),
			tokens->heredoc_expand,
			tokens->expanded);
		if (tokens->quote_map)
		{
			printf("quote_map: \"");
			for (size_t i = 0; tokens->quote_map[i]; i++)
			{
				char q = tokens->quote_map[i];
				if (q == '0') printf("0");
				else if (q == '1') printf("1");
				else if (q == '2') printf("2");
				else printf("?");
			}
			printf("\"\n");
		}
		tokens = tokens->next;
	}
}

void	run_test(const char *input, const char *expected_expander, const char *block_label)
{
	t_token	*tokens = lexer((char *)input);
	char	actual[2048] = "";
	char	tmp_buf[512];

	if (!tokens)
	{
		if (strcmp(expected_expander, "") == 0 || strcmp(expected_expander, "NULL") == 0)
		{
			printf(BLUE "Expander test_%d (%s) " RESET, g_test_num, block_label);
			printf(GREEN "✅ Ok\n" RESET);
			// printf("==== INPUT: \"%s\" ====\n" RESET, input);
			// printf(YELLOW "Expected: %s\n" RESET, expected_expander);
			// printf(GREEN "Actual  : NULL\n" RESET);
			// print_tokens_verbose(tokens);
			// printf("\n");
		}
		else
		{
			printf(RED "\nExpander test_%d (%s) " RESET, g_test_num, block_label);
			printf(RED "❌ FAIL\n" RESET);
			printf("==== INPUT: \"%s\" ====\n" RESET, input);
			printf(YELLOW "Expected: %s\n" RESET, expected_expander);
			printf(RED "Actual  : NULL\n" RESET);
			print_tokens_verbose(tokens);
			printf("\n");
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
		ft_strcat(actual, tmp_buf);
		if (tmp->next)
			ft_strcat(actual, ", ");
		tmp = tmp->next;
	}

	if (strcmp(actual, expected_expander) == 0)
	{
		printf(BLUE "Expander test_%d (%s) " RESET, g_test_num, block_label);
		printf(GREEN "✅ Ok\n" RESET);
		// printf("==== INPUT: \"%s\" ====\n" RESET, input);
		// printf(YELLOW "Expected: %s\n" RESET, expected_expander);
		// printf(GREEN "Actual  : %s\n" RESET, actual);
		// print_tokens_verbose(tokens);
		// printf("\n");
	}
	else
	{
		printf(RED "\nExpander test_%d (%s) " RESET, g_test_num, block_label);
		printf(RED "❌ FAIL\n" RESET);
		printf("==== INPUT: \"%s\" ====\n" RESET, input);
		printf(YELLOW "Expected: %s\n" RESET, expected_expander);
		printf(RED "Actual  : %s\n" RESET, actual);
		print_tokens_verbose(tokens);
		printf("\n");
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

// подключаем нужные блоки
extern const t_test_block basic_block;
extern const t_test_block dollar_block;
extern const t_test_block quoting_block;
extern const t_test_block invalid_quotting_block;
extern const t_test_block redirection_block;
extern const t_test_block heredoc_block;
extern const t_test_block logical_block;
extern const t_test_block comment_block;
extern const t_test_block paren_block;
extern const t_test_block escape_block;

int	main(void)
{
	run_block(&basic_block);
	run_block(&dollar_block);
	// run_block(&quoting_block);
	// run_block(&invalid_quotting_block);
	// run_block(&redirection_block);
	run_block(&heredoc_block);
	// run_block(&logical_block);
	// run_block(&comment_block);
	run_block(&paren_block);
	// run_block(&escape_block);
	report_failed_tests();
	return (0);
}
