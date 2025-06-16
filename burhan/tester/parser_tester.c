/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:05:33 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/16 18:39:47 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.h"

int g_test_num = 1;
int g_failed_tests[1024];
int g_failed_count = 0;

void	print_command_line(t_ast_node *node, char *buf)
{
	if (!node)
		return;
	if (node->type == NODE_COMMAND && node->command)
	{
		for (int i = 0; node->command->argv && node->command->argv[i]; i++)
		{
			strcat(buf, node->command->argv[i]);
			if (node->command->argv[i + 1])
				strcat(buf, " ");
		}
	}
	else
	{
		print_command_line(node->left, buf);
		switch (node->type)
		{
			case NODE_PIPE: strcat(buf, " | "); break;
			case NODE_AND:  strcat(buf, " && "); break;
			case NODE_OR:   strcat(buf, " || "); break;
			case NODE_SUBSHELL: strcat(buf, " (subshell) "); break;
			default: break;
		}
		print_command_line(node->right, buf);
	}
}

void	print_ast_tree(const t_ast_node *node, int depth)
{
	if (!node)
		return;

	for (int i = 0; i < depth; i++)
		printf("    ");

	switch (node->type)
	{
		case NODE_COMMAND:
			printf("CMD\n");
			for (int i = 0; node->command && node->command->argv && node->command->argv[i]; i++)
			{
				// for (int j = 0; j < depth + 1; j++) printf(" ");
				printf("└── %s\n", node->command->argv[i]);
			}
			break;
		case NODE_PIPE:     printf("PIPE\n"); break;
		case NODE_AND:      printf("AND\n"); break;
		case NODE_OR:       printf("OR\n"); break;
		case NODE_SUBSHELL: printf("SUBSHELL\n"); break;
		default:            printf("UNKNOWN\n"); break;
	}

	print_ast_tree(node->left, depth + 1);
	print_ast_tree(node->right, depth + 1);
}

void	run_parser_test(const t_test_case *test, const char *block_label)
{
	t_token *tokens = lexer((char *)test->input);
	t_ast_node *ast = parser(tokens);

	char actual_cmdline[1024] = {0};

	if (!ast && strcmp(test->expected_parser, "NULL") == 0)
	{
		printf(BLUE "\nParser test_%d (%s) " RESET, g_test_num, block_label);
		printf(GREEN "✅ Ok (NULL tree)\n" RESET);
	}
	else if (!ast)
	{
		printf(RED "\nParser test_%d (%s) ❌ FAIL\n" RESET, g_test_num, block_label);
		printf("==== INPUT: \"%s\" ====\n", test->input);
		printf(YELLOW "Expected CMD: %s\n" RESET, test->expected_parser);
		printf(RED    "Actual   CMD: NULL\n" RESET);
		g_failed_tests[g_failed_count++] = g_test_num;
	}
	else
	{
		print_command_line(ast, actual_cmdline);

		if (strcmp(actual_cmdline, test->expected_parser) != 0)
		{
			printf(RED "\nParser test_%d (%s) ❌ FAIL\n" RESET, g_test_num, block_label);
			printf("==== INPUT: \"%s\" ====\n", test->input);
			printf(YELLOW "Expected CMD: %s\n" RESET, test->expected_parser);
			printf(RED    "Actual   CMD: %s\n" RESET, actual_cmdline);
			g_failed_tests[g_failed_count++] = g_test_num;
		}
		else
		{
			printf(BLUE "\nParser test_%d (%s) " RESET, g_test_num, block_label);
			printf(GREEN "✅ CMD Ok\n" RESET);
		}

		if (test->expected_ast && strlen(test->expected_ast) > 0)
		{
			printf(YELLOW "Expected AST:\n%s\n" RESET, test->expected_ast);
			printf(RED "Actual AST:\n" RESET);
			print_ast_tree(ast, 0);
		}
	}
	free_ast(ast);
	clean_token_list(tokens);
	g_test_num++;
}

void	run_block(const t_test_block *block)
{
	printf(CYAN "\n=== %s ===\n" RESET, block->block_name);
	for (int i = 0; i < block->count; i++)
		run_parser_test(&block->cases[i], block->block_label);
	printf(CYAN "=== END OF %s ===\n" RESET, block->block_name);
}

void	report_failed_tests(void)
{
	if (g_failed_count == 0)
	{
		printf(GREEN "\nAll parser tests passed!\n" RESET);
		return;
	}
	printf(RED "\n❌ Failed parser test cases:\n" RESET);
	for (int i = 0; i < g_failed_count; i++)
		printf(RED "❌ test_%d\n" RESET, g_failed_tests[i]);
}

// подключаем нужные блоки
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
