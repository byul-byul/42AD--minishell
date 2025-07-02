/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:06:07 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 15:47:50 by bhajili          ###   ########.fr       */
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
		printf("token: %-16s | type: %-13s | heredoc_expand: %d | expanded: %d |\n",
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

void	run_test(const char *input, const char *expected_desc, const char *block_label)
{
	t_token	*tokens = lexer((char *)input);
	char	actual[2048] = "";
	char	tmp_buf[512];

	if (!tokens)
	{
		if (strcmp("NULL", expected_desc) == 0)
		{
			printf(BLUE "Lexer test_%d (%s) " RESET, g_test_num, block_label);
			printf(GREEN "✅ Ok\n" RESET);
			// printf("==== INPUT: \"%s\" ====\n" RESET, input);
			// printf(YELLOW "Expected: %s\n" RESET, expected_desc);
			// printf(GREEN "Actual  : NULL\n");
			// print_tokens_verbose(tokens);
			// printf("\n");
		}
		else
		{
			printf(RED "\nLexer test_%d (%s) " RESET, g_test_num, block_label);
			printf(RED "❌ FAIL\n" RESET);
			printf("==== INPUT: \"%s\" ====\n" RESET, input);
			printf(YELLOW "Expected: %s\n" RESET, expected_desc);
			printf(RED "Actual  : NULL\n");
			print_tokens_verbose(tokens);
			printf("\n");
			g_failed_tests[g_failed_count++] = g_test_num;
		}
		g_test_num++;
		return;
	}

	t_token *tmp = tokens;
	while (tmp)
	{
		sprintf(tmp_buf, "%s -> '%s'", get_type_name(tmp->type), tmp->value);
		strcat(actual, tmp_buf);
		if (tmp->next)
			strcat(actual, ", ");
		tmp = tmp->next;
	}
	if (strcmp(actual, expected_desc) == 0)
	{
		printf(BLUE "Lexer test_%d (%s) " RESET, g_test_num, block_label);
		printf(GREEN "✅ Ok\n" RESET);
		// printf("==== INPUT: \"%s\" ====\n" RESET, input);
		// printf(YELLOW "Expected: %s\n" RESET, expected_desc);
		// printf(GREEN "Actual  : %s\n" RESET, actual);
		// print_tokens_verbose(tokens);
		// printf("\n");
	}
	else
	{
		printf(RED "\nLexer test_%d (%s) " RESET, g_test_num, block_label);
		printf(RED "❌ FAIL\n" RESET);
		printf("==== INPUT: \"%s\" ====\n" RESET, input);
		printf(YELLOW "Expected: %s\n" RESET, expected_desc);
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
		run_test(block->cases[i].input, block->cases[i].expected_lexer, block->block_label);
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
	run_block(&basic_block);
	run_block(&dollar_block);
	run_block(&quoting_block);
	run_block(&invalid_quotting_block);
	run_block(&redirection_block);
	run_block(&heredoc_block);
	run_block(&logical_block);
	run_block(&comment_block);
	run_block(&paren_block);
	// run_block(&escape_block);
	report_failed_tests();
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include "../incls/lexer.h"

// #define GREEN   "\033[32m"
// #define RED     "\033[31m"
// #define RESET   "\033[0m"
// #define YELLOW  "\033[33m"
// #define BLUE    "\033[34m"

// int g_test_num = 1;
// int g_failed_tests[1024];
// int g_failed_count = 0;

// void print_token_details(t_token *tokens)
// {
// 	while (tokens)
// 	{
// 		printf("value: %-16s | type: %-13s | quoted: %d | heredoc_expand: %d | expanded: %d\n",
// 			tokens->value,
// 			tokens->type == WORD ? "WORD" :
// 			tokens->type == PIPE ? "PIPE" :
// 			tokens->type == REDIR_IN ? "REDIR_IN" :
// 			tokens->type == REDIR_OUT ? "REDIR_OUT" :
// 			tokens->type == HEREDOC ? "HEREDOC" :
// 			tokens->type == APPEND ? "APPEND" :
// 			tokens->type == LOGICAL_AND ? "AND" :
// 			tokens->type == LOGICAL_OR ? "OR" :
// 			tokens->type == OPEN_PAREN ? "OPEN_PAREN" :
// 			tokens->type == CLOSE_PAREN ? "CLOSE_PAREN" : "UNKNOWN",
// 			tokens->quoted,
// 			tokens->heredoc_expand,
// 			tokens->expanded);
// 		printf(GREEN "✅ Ok: \"%s\"\n" RESET, tokens->value);
// 		tokens = tokens->next;
// 	}
// }

// void run_test(const char *input, const char *expected_desc, const char *bash_desc)
// {
// 	(void)bash_desc;
// 	t_token *tokens = lexer((char *)input, 0);

// 	printf(BLUE "\ntest_%d\n" RESET, g_test_num);
// 	printf(BLUE "==== INPUT: \"%s\" ====\n" RESET, input);
// 	printf(YELLOW "Expected: %s\n" RESET, expected_desc);

// 	if (!tokens)
// 	{
// 		if (strcmp(expected_desc, "NULL") == 0 || strstr(expected_desc, "NULL"))
// 			printf(GREEN "✅ Ok: NULL\n" RESET);
// 		else
// 		{
// 			printf(RED "NULL\n" RESET);
// 			g_failed_tests[g_failed_count++] = g_test_num++;
// 			return;
// 		}
// 		g_test_num++;
// 		return;
// 	}
// 	print_token_details(tokens);
// 	clean_token_list(tokens);
// 	g_test_num++;
// }

// void report_failed_tests(void)
// {
// 	if (g_failed_count == 0)
// 	{
// 		printf(GREEN "\nAll tests passed!\n" RESET);
// 		return;
// 	}
// 	printf(RED "\nFailed tests: ");
// 	for (int i = 0; i < g_failed_count; i++)
// 		printf("%d ", g_failed_tests[i]);
// 	printf("\n" RESET);
// }

// int main(void)
// {
// 	// BASIC
// 	printf(BLUE "\n=== BASIC TOKEN TESTS ===\n" RESET);
// 	run_test("ls", "WORD -> 'ls'", "ls");
// 	run_test("echo test", "WORD -> 'echo', WORD -> 'test'", "echo, test");
// 	run_test("echo 123 abc", "WORD -> 'echo', WORD -> '123', WORD -> 'abc'", "three words");
// 	run_test("a=b", "WORD -> 'a=b'", "assignment like string");
// 	run_test("true && false", "WORD, AND, WORD", "basic logic");
// 	run_test("!", "WORD -> '!'", "negation");
// 	run_test("true || false && true", "WORD, OR, WORD, AND, WORD", "logic chain");
// 	printf("=== END ===\n");

// 	// DOLLAR
// 	printf(BLUE "\n=== DOLLAR EXPANSION TESTS ===\n" RESET);
// 	run_test("echo $USER", "WORD -> 'echo', WORD (expanded)", "$USER");
// 	run_test("echo $?", "WORD -> 'echo', WORD", "$?");
// 	run_test("echo $", "WORD -> 'echo', WORD -> '$'", "lonely dollar");
// 	run_test("echo $1", "WORD -> 'echo', WORD -> '$1'", "$1");
// 	run_test("echo $$", "WORD -> 'echo', WORD -> '$$'", "$$");
// 	run_test("echo $@", "WORD -> 'echo', WORD -> '$@'", "$@");
// 	run_test("echo $VAR$VAR2", "expanded chain", "double var");
// 	run_test("echo '$USER'", "quoted no expand", "single quotes");
// 	run_test("echo \"$USER\"", "quoted expand", "double quotes");
// 	run_test("echo ${USER}", "brace expansion", "braced var");
// 	printf("=== END ===\n");

// 	// QUOTING
// 	printf(BLUE "\n=== QUOTING TESTS ===\n" RESET);
// 	run_test("'a b'", "WORD (quoted=SINGLE)", "space inside single");
// 	run_test("\"a b\"", "WORD (quoted=DOUBLE)", "space inside double");
// 	run_test("\"a'$b\"c\"", "NULL", "mixed nesting");
// 	run_test("\"unterminated", "NULL", "open double quote");
// 	run_test("'unterminated", "NULL", "open single quote");
// 	run_test("''", "WORD (empty)", "empty single quote");
// 	run_test("\"\"", "WORD (empty)", "empty double quote");
// 	run_test("a\"b\"c", "WORD -> 'abc'", "merge with quotes");
// 	run_test("a'b'c", "WORD -> 'abc'", "merge with single quotes");
// 	run_test("\"a\"'b'", "WORD -> 'ab'", "double then single");
// 	printf("=== END ===\n");

// 	// INVALID QUOTES
// 	printf(BLUE "\n=== INVALID QUOTES ===\n" RESET);
// 	run_test("\"a'b", "NULL", "open double, then single");
// 	run_test("'a\"b", "NULL", "open single, then double");
// 	run_test("\"a\"'b", "WORD, NULL", "terminated then invalid");
// 	run_test("\"a''", "NULL", "unbalanced closing");
// 	run_test("''\"", "NULL", "bad combo");
// 	run_test("\"\"", "WORD (empty)", "balanced");
// 	run_test("'abc", "NULL", "missing closing");
// 	run_test("\"abc", "NULL", "missing closing");
// 	printf("=== END ===\n");

// 	// REDIRECTS
// 	printf(BLUE "\n=== REDIRECTS ===\n" RESET);
// 	run_test("< file", "REDIR_IN, WORD", "< file");
// 	run_test("> file", "REDIR_OUT, WORD", "> file");
// 	run_test(">> file", "APPEND, WORD", ">> file");
// 	run_test("<< word", "HEREDOC, WORD", "<<");
// 	run_test("<> file", "REDIR_IN, REDIR_OUT, WORD", "invalid combo");
// 	run_test("<<< EOF", "APPEND, HEREDOC, WORD", "triple redirect");
// 	run_test("<<>>", "HEREDOC, APPEND", "weird combo");
// 	run_test(">", "REDIR_OUT", "redirect only");
// 	run_test(">>", "APPEND", "append only");
// 	run_test("<", "REDIR_IN", "input only");
// 	printf("=== END ===\n");

// 	// HEREDOC
// 	printf(BLUE "\n=== HEREDOC + EXPAND ===\n" RESET);
// 	run_test("<< 'EOF'", "HEREDOC, WORD (quoted)", "no expand");
// 	run_test("<< \"$EOF\"", "HEREDOC, WORD (quoted=DOUBLE)", "expand");
// 	run_test("<<EOF", "HEREDOC, WORD", "plain");
// 	run_test("<<", "HEREDOC", "alone");
// 	run_test("<<\"\"", "HEREDOC, WORD (empty)", "empty delimiter");
// 	run_test("<<' '", "HEREDOC, WORD (space)", "space");
// 	run_test("<<''", "HEREDOC, WORD (empty)", "empty single");
// 	run_test("<<$?", "HEREDOC, WORD", "$? as limiter");
// 	run_test("<<|", "HEREDOC, PIPE", "pipe as delimiter");
// 	printf("=== END ===\n");

// 	// PIPES & LOGICAL
// 	printf(BLUE "\n=== PIPES & LOGICALS ===\n" RESET);
// 	run_test("cmd1 | cmd2", "WORD, PIPE, WORD", "pipe");
// 	run_test("cmd1||cmd2", "WORD, OR, WORD", "OR no space");
// 	run_test("cmd1&&cmd2", "WORD, AND, WORD", "AND no space");
// 	run_test("||", "OR", "only OR");
// 	run_test("| |", "PIPE, PIPE", "double pipes");
// 	run_test("|||", "PIPE, PIPE, PIPE", "triple");
// 	run_test("&&||", "AND, OR", "mix");
// 	run_test("cmd &&", "WORD, AND", "dangling AND");
// 	run_test("cmd ||", "WORD, OR", "dangling OR");
// 	run_test("cmd1&&", "WORD, AND", "end with AND");
// 	run_test("cmd1||", "WORD, OR", "end with OR");
// 	printf("=== END ===\n");

// 	// PARENTHESIS
// 	printf(BLUE "\n=== PARENTHESIS ===\n" RESET);
// 	run_test("(true)", "OPEN_PAREN, WORD, CLOSE_PAREN", "simple");
// 	run_test("((cmd))", "OPEN_PAREN, OPEN_PAREN, WORD, CLOSE_PAREN, CLOSE_PAREN", "nested");
// 	run_test("(", "OPEN_PAREN", "only open");
// 	run_test(")", "CLOSE_PAREN", "only close");
// 	run_test("())", "OPEN_PAREN, CLOSE_PAREN, CLOSE_PAREN", "misbalance");
// 	run_test("(cmd", "OPEN_PAREN, WORD", "unclosed");
// 	printf("=== END ===\n");

// 	// ESCAPING
// 	printf(BLUE "\n=== ESCAPING ===\n" RESET);
// 	run_test("echo \\$USER", "WORD -> 'echo', WORD -> '$USER'", "escaped dollar");
// 	run_test("echo \\\"", "WORD -> 'echo', WORD -> '\"'", "escaped quote");
// 	run_test("echo \\\\", "WORD -> 'echo', WORD -> '\\'", "escaped backslash");
// 	run_test("\\|", "WORD -> '|'", "escaped pipe");
// 	run_test("cmd\\&&", "WORD", "escaped logic");
// 	run_test("\\ ", "WORD -> ' '", "escaped space");
// 	printf("=== END ===\n");

// 	// META-COMBO TRASH
// 	printf(BLUE "\n=== META TRASH COMBOS ===\n" RESET);
// 	run_test("><", "REDIR_OUT, REDIR_IN", "swap redirects");
// 	run_test(">|", "REDIR_OUT, PIPE", "redirect pipe");
// 	run_test(">>|", "APPEND, PIPE", "append pipe");
// 	run_test("|>>", "PIPE, APPEND", "pipe append");
// 	run_test("&&>", "AND, REDIR_OUT", "logic and redirect");
// 	run_test("||<", "OR, REDIR_IN", "OR and input");
// 	run_test("<<|", "HEREDOC, PIPE", "heredoc pipe");
// 	run_test("<||", "REDIR_IN, OR", "in and or");
// 	printf("=== END ===\n");

// 	// SPACING CHAOS
// 	printf(BLUE "\n=== SPACING & WHITESPACE ===\n" RESET);
// 	run_test("  ls    -la", "WORD, WORD", "extra space");
// 	run_test("\tls\t-a", "WORD, WORD", "tabs");
// 	run_test("ls \n -a", "WORD, WORD", "newline");
// 	run_test("ls \v-a", "WORD, WORD", "vertical tab");
// 	run_test("ls\f-a", "WORD, WORD", "form feed");
// 	run_test("ls\r-a", "WORD, WORD", "carriage return");
// 	printf("=== END ===\n");

// 	// BACKTICKS & COMMAND SUBSTITUTION
// 	printf(BLUE "\n=== BACKTICKS & COMMAND SUBSTITUTION ===\n" RESET);
// 	run_test("`echo hi`", "WORD (backticks)", "legacy cmd subs");
// 	run_test("echo `whoami`", "WORD, WORD", "inline backticks");
// 	run_test("echo $(whoami)", "WORD, WORD", "modern subshell");
// 	run_test("`unterminated", "NULL", "unterminated backtick");
// 	run_test("`a`b`", "NULL", "invalid combo");
// 	printf("=== END ===\n");

// 	// EDGE CASES
// 	printf(BLUE "\n=== EDGE CASES ===\n" RESET);
// 	run_test("", "NULL", "empty");
// 	run_test("   ", "NULL", "spaces only");
// 	run_test(";;", "WORD, WORD", "strange semicolons");
// 	run_test("echo \"", "NULL", "open quote");
// 	run_test("echo \'", "NULL", "open single");
// 	run_test("\"test", "NULL", "broken quote");
// 	run_test("echo \"multi\nline\"", "NULL or fail", "multi-line quote");
// 	run_test("echo 'multi\nline'", "NULL or fail", "multi-line single");
// 	run_test("\0", "NULL", "null byte");
// 	printf("=== END ===\n");

// 	report_failed_tests();
// 	return (0);
// }





// #include <stdio.h>
// #include <string.h>
// #include "../incls/minishell.h"
// #include "../incls/lexer.h"

// #define RED     "\033[0;31m"
// #define GREEN   "\033[0;32m"
// #define YELLOW  "\033[0;33m"
// #define CYAN    "\033[0;36m"
// #define RESET   "\033[0m"

// void	clean_token_list(t_token *token_list);

// static const char	*g_token_names[] = {
// 	[WORD] = "WORD",
// 	[PIPE] = "PIPE",
// 	[REDIR_IN] = "REDIR_IN",
// 	[REDIR_OUT] = "REDIR_OUT",
// 	[HEREDOC] = "HEREDOC",
// 	[APPEND] = "APPEND",
// 	[LOGICAL_AND] = "LOGICAL_AND",
// 	[LOGICAL_OR] = "LOGICAL_OR",
// 	[OPEN_PAREN] = "OPEN_PAREN",
// 	[CLOSE_PAREN] = "CLOSE_PAREN"
// };

// void	validate_tokens(t_token *token, const char **expected)
// {
// 	int	i = 0;

// 	while (token && expected[i])
// 	{
// 		// if (token->value && strcmp(token->value, expected[i]) == 0)
// 		if (token->value && expected[i] && strcmp(token->value, expected[i]) == 0)
// 			printf(GREEN "✅ Ok: \"%s\"\n" RESET, expected[i]);
// 		else
// 			printf(RED "❌ Fail: expected \"%s\", got \"%s\"\n" RESET,
// 				expected[i], token->value ? token->value : "(null)");
// 		token = token->next;
// 		i++;
// 	}
// 	if (expected[i])
// 		printf(RED "❌ Fail: missing token \"%s\"\n" RESET, expected[i]);
// 	if (token)
// 		// printf(RED "❌ Fail: extra token \"%s\"\n" RESET, token->value);
// 		if (token)
// 		printf(RED "❌ Fail: extra token \"%s\"\n" RESET, token->value ? token->value : "(null)");
// }

// void	print_token(t_token *token)
// {
// 	while (token)
// 	{
// 		printf(YELLOW "value: %-15s" RESET " | type: %-12s | quoted: %d | heredoc_expand: %d | expanded: %d\n",
// 			token->value ? token->value : "(null)",
// 			g_token_names[token->type],
// 			token->quoted,
// 			token->heredoc_expand,
// 			token->expanded);
// 		token = token->next;
// 	}
// }

// void	run_test(const char *input, int exit_status, const char **expected)
// {
// 	t_token	*token_list;
// 	static int	test_no;

// 	printf(CYAN "test_%d\n==== INPUT: \"%s\" ====\n" RESET, ++test_no, input);
// 	token_list = lexer((char *)input, exit_status);
// 	if (!token_list)
// 	{
// 		printf(RED "Lexer returned NULL (syntax error)\n\n" RESET);
// 		return ;
// 	}
// 	print_token(token_list);
// 	validate_tokens(token_list, expected);
// 	clean_token_list(token_list);
// 	printf("\n");
// }

// void	run_lexer_tests(void)
// {
// 	// === Базовые ===
// 	const char *test1[] = {"echo", "hello", "world", NULL};
// 	const char *test2[] = {"ls", "-la", "|", "grep", "src", NULL};
// 	const char *test3[] = {"cat", "<", "infile", ">", "outfile", NULL};

// 	// === Кавычки ===
// 	const char *test4[] = {"echo", "quoted text", NULL};
// 	const char *test5[] = {"echo", "quoted /home/byulbyul", NULL};

// 	// === Переменные ===
// 	const char *test6[] = {"echo", "/home/byulbyul", "42", NULL};
// 	const char *test7[] = {"echo", "", NULL};

// 	// === Heredoc ===
// 	const char *test8[] = {"cat", "<<", "EOF", NULL};
// 	const char *test9[] = {"cat", "<<", "EOF", NULL};
// 	const char *test9b[] = {"cat", "<<", "EOF", NULL};

// 	// === Логические операторы ===
// 	const char *test10[] = {"make", "&&", "make", "clean", "||", "echo", "fail", NULL};

// 	// === Пограничные случаи ===
// 	const char *test11[] = {"||", "|", ">>", ">", "<<", "<", "&&", "||", NULL};

// 	// === Смешанные кавычки ===
// 	const char *test12[] = {"echo", "'inner single'", NULL};
// 	const char *test13[] = {"echo", "\"inner double $HOME\"", NULL};
// 	const char *test14[] = {"echo", "single $HOME inside", NULL};

// 	// === Экранирование ===
// 	const char *test15[] = {"echo", "\\\"escaped", "double\\\"", NULL};
// 	const char *test16[] = {"echo", "\\\'escaped", "single\\\'", NULL};

// 	// === Последовательности $ ===
// 	const char *test17[] = {"echo", "$", "$", "$", NULL};
// 	const char *test18[] = {"echo", "$$", NULL};
// 	const char *test19[] = {"echo", "$1abc", NULL};
// 	const char *test20[] = {"echo", "$-", "$@", "$*", NULL};

// 	// === Редиректы ===
// 	const char *test21[] = {"echo", ">", NULL};
// 	const char *test22[] = {"echo", "<", NULL};
// 	const char *test23[] = {"echo", ">", "file", NULL};
// 	const char *test24[] = {"echo", ">>", "file", NULL};
// 	const char *test25[] = {"echo", "<<", "EOF", NULL};

// 	// === Wildcards ===
// 	const char *test26[] = {"echo", "*", NULL};
// 	const char *test27[] = {"ls", "src/*.c", NULL};

// 	// === Subshell ===
// 	// const char *test28[] = {"(echo", "hello)", NULL};
// 	const char *test28[] = {"(", "echo", "hello", ")", NULL};
// 	const char *test29[] = {"ls", "|", "(", "grep", "a", "&&", "cat", "b", ")", "||", "echo", "fail", NULL};

// 	// === Комбинированные ===
// 	const char *test30[] = {"echo", "/home/byulbyul", "literal", "|", "grep", "-v", "pattern", ">>", "output", NULL};
// 	const char *test31[] = {"cat", "<<", "EOF", "|", "grep", "byulbyul", "||", "echo", "fail", NULL};

// 	// === Вложенные кавычки (некорректно, но в value есть текст) ===
// 	const char *test32[] = {"echo", "this is wrong", NULL};
// 	const char *test33[] = {"echo", "this is wrong", NULL};

// 	// === Heredoc с метатокеном ===
// 	const char *test34[] = {"cat", "<<", "|", "grep", NULL};
// 	const char *test35[] = {"cat", "<<", "&&", "echo", "fail", NULL};

// 	// === Уроды и краш-тесты ===
// 	const char *test36[] = {"echo", "", NULL};
// 	const char *test37[] = {"echo", "$$$$$$$$$$", NULL};
// 	const char *test38[] = {"cat", "<<", "|", NULL};
// 	const char *test39[] = {"cat", "<<", "&&", NULL};
// 	const char *test40[] = {"echo", "(", "(", "hello", ")", ")", NULL};
// 	const char *test41[] = {"echo", ">", "|", "file", NULL};
// 	const char *test42[] = {"echo", ">>", "|", "grep", NULL};
// 	const char *test43[] = {"echo", "$\\x41", NULL};
// 	const char *test44[] = {"echo", "\\x41", NULL};
// 	const char *test45[] = {"echo", "", "unquoted-", NULL};
// 	const char *test46[] = {"cmd", "&&", "&&", "&&", "||", "||", "||", "&&", "&", NULL};
// 	const char *test47[] = {"echo", "test \"unterminated $VAR", ">>", "file", "|", "cat", "<<", "EOF", "&&", "echo", "fail", "||", "grep", "ok", NULL};

// 	// === Убийственные тесты ===
// 	const char *test48[] = {"cat", "<<", "END", NULL}; // heredoc лимитер в двойных кавычках
// 	const char *test49[] = {"cat", "<<", "EOF", NULL};     // heredoc с пробелами после
// 	const char *test50[] = {"echo", "<", ">", ">>", "<<", NULL}; // последовательность редиректов
// 	const char *test51[] = {"echo", "/", NULL};            // слэш как символ
// 	const char *test52[] = {"echo", "\\", NULL};           // одинарный escape-слэш
// 	const char *test53[] = {"echo", "'unterminated", "word", NULL}; // незакрытая кавычка, но продолжается текст
// 	const char *test54[] = {"echo", ">", "bad", "<", "data", "|", "garbage", NULL}; // мусор после токенов
// 	// const char *test55[] = {"echo", "$VAR1$VAR2$VAR3", NULL}; // конкатенация переменных
// 	const char *test55[] = {"echo", "", NULL};
// 	// const char *test56[] = {"echo", "$VAR", "text", NULL}; // echo$VAR без пробела
// 	const char *test56[] = {"echo", "", NULL};
// 	const char *test57[] = {"echostring", NULL}; // echo"string" без пробела

// 	// Heredoc с переменными и кавычками
// 	const char *test58[] = {"cat", "<<", "EOF", "|", "echo", "", "<<", "EOF2", NULL};
// 	const char *test59[] = {"cat", "<<", "`cmd`", "|", "grep", "pattern", NULL};
// 	const char *test60[] = {"cat", "<<", "EOF1", "<<", "EOF2", "<<", "EOF3", NULL};

// 	// Пустые после логических операторов
// 	const char *test61[] = {"&&", "||", NULL};

// 	// $ перед метасимволами
// 	// const char *test62[] = {"echo", "$|", "$<", "$>", "$&", "$;", NULL};
// 	const char *test62[] = {"echo", "$", "|", "$", "<", "$", ">", "$", "&", "$;", NULL};

// 	// Пайпы в начале и в конце
// 	const char *test63[] = {"|", "echo", "start", "|", "middle", "|", "end", "|", NULL};

// 	// === Тесты ===
// 	run_test("echo hello world", 0, test1);
// 	run_test("ls -la | grep src", 0, test2);
// 	run_test("cat < infile > outfile", 0, test3);
// 	run_test("echo 'quoted text'", 0, test4);
// 	run_test("echo \"quoted $HOME\"", 0, test5);
// 	run_test("echo $HOME $?", 42, test6);
// 	run_test("echo $UNSET_VAR", 0, test7);
// 	run_test("cat << EOF", 0, test8);
// 	run_test("cat << 'EOF'", 0, test9);
// 	run_test("make && make clean || echo fail", 0, test10);
// 	run_test("||| >>> <<< && ||", 0, test11);
// 	run_test("echo \"'inner single'\"", 0, test12);
// 	run_test("echo '\"inner double $HOME\"'", 0, test13);
// 	run_test("echo 'single $HOME inside'", 0, test14);
// 	run_test("echo \\\"escaped double\\\"", 0, test15);
// 	run_test("echo \\\'escaped single\\\'", 0, test16);
// 	run_test("echo $ $ $", 0, test17);
// 	run_test("echo $$", 0, test18);
// 	run_test("echo $1abc", 0, test19);
// 	run_test("echo $- $@ $*", 0, test20);
// 	run_test("echo >", 0, test21);
// 	run_test("echo <", 0, test22);
// 	run_test("echo>file", 0, test23);
// 	run_test("echo>>file", 0, test24);
// 	run_test("echo<<EOF", 0, test25);
// 	run_test("echo *", 0, test26);
// 	run_test("ls src/*.c", 0, test27);
// 	run_test("(echo hello)", 0, test28);
// 	run_test("ls | (grep a && cat b) || echo fail", 0, test29);
// 	run_test("echo \"$HOME\" 'literal' | grep -v 'pattern' >> output", 0, test30);
// 	run_test("cat << EOF | grep \"$USER\" || echo 'fail'", 0, test31);
// 	run_test("echo 'this 'is' wrong'", 0, test32);
// 	run_test("echo \"this \"is\" wrong\"", 0, test33);
// 	run_test("cat << | grep", 0, test34);
// 	run_test("cat << && echo fail", 0, test35);
// 	run_test("echo $A_B_C_123_456_xXx", 0, test36);
// 	run_test("echo $$$$$$$$$$", 0, test37);
// 	run_test("cat << |", 0, test38);
// 	run_test("cat << &&", 0, test39);
// 	run_test("echo ((hello))", 0, test40);
// 	run_test("echo >| file", 0, test41);
// 	run_test("echo >>| grep", 0, test42);
// 	run_test("echo $'\\x41'", 0, test43);
// 	run_test("echo \\x41", 0, test44);
// 	run_test("echo \"$EMPTY\" unquoted-$EMPTY", 0, test45);
// 	run_test("cmd &&&&&&|| |||| &&&", 0, test46);
// 	run_test("echo 'test \"unterminated $VAR' >>file | cat << 'EOF' && echo fail || grep ok", 0, test47);

// 	// === Прогоним новые тесты ===
// 	run_test("cat << \"END\"", 0, test48);
// 	run_test("cat <<  EOF   ", 0, test49);
// 	run_test("echo < > >> <<", 0, test50);
// 	run_test("echo /", 0, test51);
// 	run_test("echo \\", 0, test52);
// 	run_test("echo 'unterminated word", 0, test53);
// 	run_test("echo > bad < data | garbage", 0, test54);
// 	run_test("echo $VAR1$VAR2$VAR3", 0, test55);
// 	run_test("echo $VARtext", 0, test56);
// 	run_test("echo\"string\"", 0, test57);

// 	run_test("cat << EOF | echo $VAR << 'EOF2'", 0, test58);
// 	run_test("cat << `cmd` | grep pattern", 0, test59);
// 	run_test("cat << EOF1 << EOF2 << 'EOF3'", 0, test60);
// 	run_test("&& ||", 0, test61);
// 	run_test("echo $| $< $> $& $;", 0, test62);
// 	run_test("| echo start | middle | end |", 0, test63);

// 	run_test("cat << \"EOF\"", 0, test9b); //test64
// }

// int main(void)
// {
// 	run_lexer_tests();
// 	return (0);
// }
