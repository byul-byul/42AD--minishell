/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tester.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 18:05:33 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/28 18:09:20 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../incls/minishell.h"
#include "../incls/parser.h"

#define CYAN  "\033[0;36m"
#define GREEN "\033[0;32m"
#define RED   "\033[0;31m"
#define RESET "\033[0m"

static int test_no;

void	print_ast(t_ast_node *node, int depth)
{
	if (!node)
		return;
	for (int i = 0; i < depth; i++)
		printf("  ");
	switch (node->type)
	{
		case NODE_COMMAND:
			printf(GREEN "COMMAND:" RESET);
			for (int i = 0; node->command && node->command->argv && node->command->argv[i]; i++)
				printf(" \"%s\"", node->command->argv[i]);
			printf("\n");
			break;
		case NODE_PIPE:
			printf("PIPE\n");
			break;
		case NODE_AND:
			printf("AND\n");
			break;
		case NODE_OR:
			printf("OR\n");
			break;
		case NODE_SUBSHELL:
			printf("SUBSHELL\n");
			break;
	}
	print_ast(node->left, depth + 1);
	print_ast(node->right, depth + 1);
}

void	run_parser_test(const char *input, int exit_status)
{
	t_token		*token_list;
	t_ast_node	*ast;

	printf(CYAN "test_%d\n==== INPUT: \"%s\" ====\n" RESET, ++test_no, input);
	token_list = lexer((char *)input, exit_status);
	if (!token_list)
	{
		printf(RED "Lexer returned NULL (syntax error)\n\n" RESET);
		return;
	}
	ast = parser(token_list);
	if (!ast)
		printf(RED "Parser returned NULL (syntax error)\n" RESET);
	else
		print_ast(ast, 0);
	clean_token_list(token_list);
	free_ast(ast);
	printf("\n");
}

int	main(void)
{
	run_parser_test("echo hello", 0);
	run_parser_test("ls | grep src", 0);
	run_parser_test("(ls -la)", 0);
	run_parser_test("(ls -la | grep .c) && echo done", 0);
	run_parser_test("cat < infile > outfile", 0);
	run_parser_test("make && make clean || echo fail", 0);
	run_parser_test("ls | | grep", 0);
	run_parser_test("echo ||", 0);
	run_parser_test("|| echo", 0);
	run_parser_test("(echo hi", 0); // незакрытая скобка
	run_parser_test(")", 0);        // лишняя закрывающая
	run_parser_test("echo hello || ls || date", 0);

	return (0);
}
