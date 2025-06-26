/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:05:33 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 19:40:13 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

int g_test_num = 1;
int g_failed_tests[1024];
int g_failed_count = 0;

int	strcmp_trimmed(const char *a, const char *b)
{
	while (*a == ' ' || *a == '\n') a++;
	while (*b == ' ' || *b == '\n') b++;

	size_t len_a = strlen(a);
	size_t len_b = strlen(b);

	while (len_a > 0 && (a[len_a - 1] == ' ' || a[len_a - 1] == '\n')) len_a--;
	while (len_b > 0 && (b[len_b - 1] == ' ' || b[len_b - 1] == '\n')) len_b--;

	if (len_a != len_b)
		return 1;
	return strncmp(a, b, len_a);
}

// Вспомогательная функция: построение строки по дереву AST
void	build_ast_string(const t_ast_node *node, int depth, char *buf, size_t bufsize)
{
	char line[256];

	if (!node)
		return;

	// Отступ + тип узла
	for (int i = 0; i < depth * 4 && i < (int)sizeof(line) - 1; i++)
		line[i] = ' ';
	line[depth * 4] = '\0';

	switch (node->type)
	{
		case NODE_COMMAND:
			ft_strlcat(buf, line, bufsize);
			ft_strlcat(buf, "CMD\n", bufsize);
			if (node->command && node->command->argv)
			{
				int count = 0;
				while (node->command->argv[count])
					count++;
				for (int i = 0; i < count; i++)
				{
					const char *prefix = (i == count - 1) ? "└── " : "├── ";
					snprintf(line, sizeof(line), "%*s%s%s\n", depth * 4, "", prefix, node->command->argv[i]);
					ft_strlcat(buf, line, bufsize);
				}
			}
			break;
		case NODE_PIPE:
			ft_strlcat(buf, line, bufsize);
			ft_strlcat(buf, "PIPE\n", bufsize);
			break;
		case NODE_AND:
			ft_strlcat(buf, line, bufsize);
			ft_strlcat(buf, "AND\n", bufsize);
			break;
		case NODE_OR:
			ft_strlcat(buf, line, bufsize);
			ft_strlcat(buf, "OR\n", bufsize);
			break;
		case NODE_SUBSHELL:
			ft_strlcat(buf, line, bufsize);
			ft_strlcat(buf, "SUBSHELL\n", bufsize);
			break;
		default:
			ft_strlcat(buf, line, bufsize);
			ft_strlcat(buf, "UNKNOWN\n", bufsize);
			break;
	}

	build_ast_string(node->left, depth + 1, buf, bufsize);
	build_ast_string(node->right, depth + 1, buf, bufsize);
}

// Печать AST для отладки (визуальная версия)
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
				printf("└── %s\n", node->command->argv[i]);
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

void	ast_to_cmd_string(t_ast_node *node, char *buffer, size_t bufsize)
{
	if (!node || node->type != NODE_COMMAND || !node->command || !node->command->argv)
	{
		ft_strlcpy(buffer, "NULL", bufsize);
		return;
	}

	buffer[0] = '\0';
	for (int i = 0; node->command->argv[i]; i++)
	{
		const char *arg = node->command->argv[i];
		if (arg[0] == '\0')
			ft_strlcat(buffer, "\"\"", bufsize);  // empty string shown as ""
		else
			ft_strlcat(buffer, arg, bufsize);

		if (node->command->argv[i + 1])
			ft_strlcat(buffer, " ", bufsize);
	}
}

void	run_test(const char *input, const char *expected_parser, const char *expected_ast, const char *block_label)
{
	t_token	*tokens = lexer((char *)input);
	expander(tokens, 0);
	t_ast_node *ast = parser(tokens);

	char actual_parser[1024] = "";
	char actual_ast[4096] = "";

	if (ast)
	{
		ast_to_cmd_string(ast, actual_parser, sizeof(actual_parser));
		build_ast_string(ast, 0, actual_ast, sizeof(actual_ast));
	}
	else
	{
		strcpy(actual_parser, "NULL");
		strcpy(actual_ast, "[EMPTY]");
	}

	int ok_parser = strcmp_trimmed(expected_parser, actual_parser) == 0;
	int ok_ast = strcmp_trimmed(expected_ast, actual_ast) == 0;
	int is_ok = ok_parser && ok_ast;

	printf(is_ok ? BLUE "\nParser test_%d (%s) " RESET : RED "\nParser test_%d (%s) " RESET,
		g_test_num, block_label);
	printf(is_ok ? GREEN "✅ Ok\n" RESET : RED "❌ FAIL\n" RESET);

	printf("==== INPUT: \"%s\" ====\n", input);
	printf(YELLOW "Expected PARSER: %s\n" RESET, expected_parser);
	printf(ok_parser ? GREEN : RED);
	printf("Actual   PARSER: %s\n" RESET, actual_parser);

	printf(YELLOW "Expected AST   : %s\n" RESET, expected_ast);
	printf(ok_ast ? GREEN : RED);
	printf("Actual   AST   : %s\n" RESET, actual_ast);

	if (!is_ok)
		g_failed_tests[g_failed_count++] = g_test_num;

	clean_token_list(tokens);
	free_ast(ast);
	g_test_num++;
}

void	run_block(const t_test_block *block)
{
	printf(CYAN "\n=== %s ===\n" RESET, block->block_name);
	for (int i = 0; i < block->count; i++)
		run_test(block->cases[i].input, block->cases[i].expected_parser, block->cases[i].expected_ast, block->block_label);
	printf(CYAN "=== END OF %s ===\n" RESET, block->block_name);
}

void	report_failed_tests(void)
{
	if (g_failed_count == 0)
	{
		printf(GREEN "\nALL TESTS PASSED!\n\n" RESET);
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
	// run_block(&basic_block);
	// run_block(&dollar_block);
	run_block(&quoting_block);
	// run_block(&invalid_quotting_block);
	// run_block(&redirection_block);
	// run_block(&heredoc_block);
	// run_block(&logical_block);
	// run_block(&comment_block);
	// run_block(&paren_block);
	// run_block(&escape_block);
	report_failed_tests();
	return (0);
}

// #include "../tester.h"

// int g_test_num = 1;
// int g_failed_tests[1024];
// int g_failed_count = 0;

// void	print_command_line(t_ast_node *node, char *buf)
// {
// 	if (!node)
// 		return;
// 	if (node->type == NODE_COMMAND && node->command)
// 	{
// 		for (int i = 0; node->command->argv && node->command->argv[i]; i++)
// 		{
// 			strcat(buf, node->command->argv[i]);
// 			if (node->command->argv[i + 1])
// 				strcat(buf, " ");
// 		}
// 	}
// 	else
// 	{
// 		print_command_line(node->left, buf);
// 		switch (node->type)
// 		{
// 			case NODE_PIPE: strcat(buf, " | "); break;
// 			case NODE_AND:  strcat(buf, " && "); break;
// 			case NODE_OR:   strcat(buf, " || "); break;
// 			case NODE_SUBSHELL: strcat(buf, " (subshell) "); break;
// 			default: break;
// 		}
// 		print_command_line(node->right, buf);
// 	}
// }

// void	print_ast_tree(const t_ast_node *node, int depth)
// {
// 	if (!node)
// 		return;

// 	for (int i = 0; i < depth; i++)
// 		printf("    ");

// 	switch (node->type)
// 	{
// 		case NODE_COMMAND:
// 			printf("CMD\n");
// 			for (int i = 0; node->command && node->command->argv && node->command->argv[i]; i++)
// 			{
// 				// for (int j = 0; j < depth + 1; j++) printf(" ");
// 				printf("└── %s\n", node->command->argv[i]);
// 			}
// 			break;
// 		case NODE_PIPE:     printf("PIPE\n"); break;
// 		case NODE_AND:      printf("AND\n"); break;
// 		case NODE_OR:       printf("OR\n"); break;
// 		case NODE_SUBSHELL: printf("SUBSHELL\n"); break;
// 		default:            printf("UNKNOWN\n"); break;
// 	}

// 	print_ast_tree(node->left, depth + 1);
// 	print_ast_tree(node->right, depth + 1);
// }

// void	run_parser_test(const t_test_case *test, const char *block_label)
// {
// 	t_token *tokens = lexer((char *)test->input);
// 	t_ast_node *ast = parser(tokens);

// 	char actual_cmdline[1024] = {0};

// 	if (!ast && strcmp_trimmed(test->expected_parser, "NULL") == 0)
// 	{
// 		printf(BLUE "\nParser test_%d (%s) " RESET, g_test_num, block_label);
// 		printf("==== INPUT: \"%s\" ====\n", test->input);
// 		printf(YELLOW "Expected CMD: %s\n" RESET, test->expected_parser);
// 		printf(GREEN  "Actual   CMD: NULL\n" RESET);
// 		printf(GREEN "✅ Ok (NULL tree)\n" RESET);
// 	}
// 	else if (!ast)
// 	{
// 		printf(RED "\nParser test_%d (%s) ❌ FAIL\n" RESET, g_test_num, block_label);
// 		printf("==== INPUT: \"%s\" ====\n", test->input);
// 		printf(YELLOW "Expected CMD: %s\n" RESET, test->expected_parser);
// 		printf(RED    "Actual   CMD: NULL\n" RESET);
// 		g_failed_tests[g_failed_count++] = g_test_num;
// 	}
// 	else
// 	{
// 		print_command_line(ast, actual_cmdline);

// 		if (strcmp_trimmed(actual_cmdline, test->expected_parser) != 0)
// 		{
// 			printf(RED "\nParser test_%d (%s) ❌ FAIL\n" RESET, g_test_num, block_label);
// 			printf("==== INPUT: \"%s\" ====\n", test->input);
// 			printf(YELLOW "Expected CMD: %s\n" RESET, test->expected_parser);
// 			printf(RED    "Actual   CMD: %s\n" RESET, actual_cmdline);
// 			g_failed_tests[g_failed_count++] = g_test_num;
// 		}
// 		else
// 		{
// 			printf(BLUE "\nParser test_%d (%s) " RESET, g_test_num, block_label);
// 			printf("==== INPUT: \"%s\" ====\n", test->input);
// 			printf(YELLOW "Expected CMD: %s\n" RESET, test->expected_parser);
// 			printf(GREEN  "Actual   CMD: %s\n" RESET, actual_cmdline);
// 			printf(GREEN "✅ CMD Ok\n" RESET);
// 		}

// 		if (test->expected_ast && strlen(test->expected_ast) > 0)
// 		{
// 			printf(YELLOW "Expected AST:\n%s\n" RESET, test->expected_ast);
// 			printf(RED "Actual AST:\n" RESET);
// 			print_ast_tree(ast, 0);
// 		}
// 	}
// 	free_ast(ast);
// 	clean_token_list(tokens);
// 	g_test_num++;
// }

// void	run_block(const t_test_block *block)
// {
// 	printf(CYAN "\n=== %s ===\n" RESET, block->block_name);
// 	for (int i = 0; i < block->count; i++)
// 		run_parser_test(&block->cases[i], block->block_label);
// 	printf(CYAN "=== END OF %s ===\n" RESET, block->block_name);
// }

// void	report_failed_tests(void)
// {
// 	if (g_failed_count == 0)
// 	{
// 		printf(GREEN "\nAll parser tests passed!\n" RESET);
// 		return;
// 	}
// 	printf(RED "\n❌ Failed parser test cases:\n" RESET);
// 	for (int i = 0; i < g_failed_count; i++)
// 		printf(RED "❌ test_%d\n" RESET, g_failed_tests[i]);
// }

// // подключаем нужные блоки
// extern const t_test_block basic_block;
// extern const t_test_block dollar_block;
// extern const t_test_block quoting_block;
// extern const t_test_block invalid_quotting_block;
// extern const t_test_block redirection_block;

// int	main(void)
// {
// 	run_block(&basic_block);
// 	// run_block(&dollar_block);
// 	// run_block(&quoting_block);
// 	// run_block(&invalid_quotting_block);
// 	// run_block(&redirection_block);
// 	report_failed_tests();
// 	return (0);
// }
