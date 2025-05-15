/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tester.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:06:07 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/15 21:02:12 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "../incls/minishell.h"
#include "../incls/lexer.h"

#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define CYAN    "\033[0;36m"
#define RESET   "\033[0m"

void	clean_token_list(t_token *token_list);

static const char	*g_token_names[] = {
	[WORD] = "WORD",
	[PIPE] = "PIPE",
	[REDIR_IN] = "REDIR_IN",
	[REDIR_OUT] = "REDIR_OUT",
	[HEREDOC] = "HEREDOC",
	[APPEND] = "APPEND",
	[LOGICAL_AND] = "LOGICAL_AND",
	[LOGICAL_OR] = "LOGICAL_OR"
};

void	validate_tokens(t_token *token, const char **expected)
{
	int	i = 0;

	while (token && expected[i])
	{
		if (token->value && strcmp(token->value, expected[i]) == 0)
			printf(GREEN "✅ Ok: \"%s\"\n" RESET, expected[i]);
		else
			printf(RED "❌ Fail: expected \"%s\", got \"%s\"\n" RESET,
				expected[i], token->value ? token->value : "(null)");
		token = token->next;
		i++;
	}
	if (expected[i])
		printf(RED "❌ Fail: missing token \"%s\"\n" RESET, expected[i]);
	if (token)
		printf(RED "❌ Fail: extra token \"%s\"\n" RESET, token->value);
}

void	print_token(t_token *token)
{
	while (token)
	{
		printf(YELLOW "value: %-15s" RESET " | type: %-12s | quoted: %d | heredoc_expand: %d | expanded: %d\n",
			token->value ? token->value : "(null)",
			g_token_names[token->type],
			token->quoted,
			token->heredoc_expand,
			token->expanded);
		token = token->next;
	}
}

void	run_test(const char *input, int exit_status, const char **expected)
{
	t_token	*token_list;

	printf(CYAN "==== INPUT: \"%s\" ====\n" RESET, input);
	token_list = lexer((char *)input, exit_status);
	if (!token_list)
	{
		printf(RED "Lexer returned NULL (syntax error)\n\n" RESET);
		return ;
	}
	print_token(token_list);
	validate_tokens(token_list, expected);
	clean_token_list(token_list);
	printf("\n");
}

void	run_lexer_tests(void)
{
	// === Базовые ===
	const char *test1[] = {"echo", "hello", "world", NULL};
	const char *test2[] = {"ls", "-la", "|", "grep", "src", NULL};
	const char *test3[] = {"cat", "<", "infile", ">", "outfile", NULL};

	// === Кавычки ===
	const char *test4[] = {"echo", "'quoted text'", NULL};
	const char *test5[] = {"echo", "\"quoted /home/byulbyul\"", NULL};

	// === Переменные ===
	const char *test6[] = {"echo", "/home/byulbyul", "42", NULL};
	const char *test7[] = {"echo", "", NULL};

	// === Heredoc ===
	const char *test8[] = {"cat", "<<", "EOF", NULL};
	const char *test9[] = {"cat", "<<", "'EOF'", NULL};

	// === Логические операторы ===
	const char *test10[] = {"make", "&&", "make", "clean", "||", "echo", "fail", NULL};

	// === Пограничные случаи ===
	const char *test11[] = {"||", "|", ">>", ">", "<<", "<", "&&", "||", NULL};

	// === Смешанные кавычки ===
	const char *test12[] = {"echo", "\"'inner single'\"", NULL};
	const char *test13[] = {"echo", "'\"inner double /home/byulbyul\"'", NULL};
	const char *test14[] = {"echo", "'single /home/byulbyul inside'", NULL};

	// === Экранирование ===
	const char *test15[] = {"echo", "\\\"escaped double\\\"", NULL};
	const char *test16[] = {"echo", "\\\'escaped single\\\'", NULL};

	// === Последовательности $ ===
	const char *test17[] = {"echo", "$", "$", "$", NULL};
	const char *test18[] = {"echo", "$$", NULL};
	const char *test19[] = {"echo", "$1abc", NULL};
	const char *test20[] = {"echo", "$-", "$@", "$*", NULL};

	// === Редиректы ===
	const char *test21[] = {"echo", ">", NULL};
	const char *test22[] = {"echo", "<", NULL};
	const char *test23[] = {"echo", ">", "file", NULL};
	const char *test24[] = {"echo", ">>", "file", NULL};
	const char *test25[] = {"echo", "<<", "EOF", NULL};

	// === Wildcards ===
	const char *test26[] = {"echo", "*", NULL};
	const char *test27[] = {"ls", "src/*.c", NULL};

	// === Subshell ===
	const char *test28[] = {"(echo", "hello)", NULL};
	const char *test29[] = {"ls", "|", "(grep", "a", "&&", "cat", "b)", "||", "echo", "fail", NULL};

	// === Комбинированные ===
	const char *test30[] = {"echo", "\"/home/byulbyul\"", "'literal'", "|", "grep", "-v", "'pattern'", ">>", "output", NULL};
	const char *test31[] = {"cat", "<<", "EOF", "|", "grep", "\"byulbyul\"", "||", "echo", "'fail'", NULL};

	// === Вложенные кавычки (некорректно, но в value есть текст) ===
	const char *test32[] = {"echo", "'this 'is' wrong'", NULL};
	const char *test33[] = {"echo", "\"this \"is\" wrong\"", NULL};

	// === Heredoc с метатокеном ===
	const char *test34[] = {"cat", "<<", "|", "grep", NULL};
	const char *test35[] = {"cat", "<<", "&&", "echo", "fail", NULL};

	// === Уроды и краш-тесты ===
	const char *test36[] = {"echo", "", NULL};
	const char *test37[] = {"echo", "$$$$$$$$$$", NULL};
	const char *test38[] = {"cat", "<<", "|", NULL};
	const char *test39[] = {"cat", "<<", "&&", NULL};
	const char *test40[] = {"echo", "((hello))", NULL};
	const char *test41[] = {"echo", ">", "|", "file", NULL};
	const char *test42[] = {"echo", ">>", "|", "grep", NULL};
	const char *test43[] = {"echo", "$'\\x41'", NULL};
	const char *test44[] = {"echo", "\\x41", NULL};
	const char *test45[] = {"echo", "\"\"", "unquoted-", NULL};
	const char *test46[] = {"cmd", "&&", "&&", "&&", "||", "||", "||", "&&", "&", NULL};
	const char *test47[] = {"echo", "'test \"unterminated '", ">>", "file", "|", "cat", "<<", "'EOF'", "&&", "echo", "fail", "||", "grep", "ok", NULL};

	// === Тесты ===
	run_test("echo hello world", 0, test1);
	run_test("ls -la | grep src", 0, test2);
	run_test("cat < infile > outfile", 0, test3);
	run_test("echo 'quoted text'", 0, test4);
	run_test("echo \"quoted $HOME\"", 0, test5);
	run_test("echo $HOME $?", 42, test6);
	run_test("echo $UNSET_VAR", 0, test7);
	run_test("cat << EOF", 0, test8);
	run_test("cat << 'EOF'", 0, test9);
	run_test("make && make clean || echo fail", 0, test10);
	run_test("||| >>> <<< && ||", 0, test11);
	run_test("echo \"'inner single'\"", 0, test12);
	run_test("echo '\"inner double $HOME\"'", 0, test13);
	run_test("echo 'single $HOME inside'", 0, test14);
	run_test("echo \\\"escaped double\\\"", 0, test15);
	run_test("echo \\\'escaped single\\\'", 0, test16);
	run_test("echo $ $ $", 0, test17);
	run_test("echo $$", 0, test18);
	run_test("echo $1abc", 0, test19);
	run_test("echo $- $@ $*", 0, test20);
	run_test("echo >", 0, test21);
	run_test("echo <", 0, test22);
	run_test("echo>file", 0, test23);
	run_test("echo>>file", 0, test24);
	run_test("echo<<EOF", 0, test25);
	run_test("echo *", 0, test26);
	run_test("ls src/*.c", 0, test27);
	run_test("(echo hello)", 0, test28);
	run_test("ls | (grep a && cat b) || echo fail", 0, test29);
	run_test("echo \"$HOME\" 'literal' | grep -v 'pattern' >> output", 0, test30);
	run_test("cat << EOF | grep \"$USER\" || echo 'fail'", 0, test31);
	run_test("echo 'this 'is' wrong'", 0, test32);
	run_test("echo \"this \"is\" wrong\"", 0, test33);
	run_test("cat << | grep", 0, test34);
	run_test("cat << && echo fail", 0, test35);
	run_test("echo $A_B_C_123_456_xXx", 0, test36);
	run_test("echo $$$$$$$$$$", 0, test37);
	run_test("cat << |", 0, test38);
	run_test("cat << &&", 0, test39);
	run_test("echo ((hello))", 0, test40);
	run_test("echo >| file", 0, test41);
	run_test("echo >>| grep", 0, test42);
	run_test("echo $'\\x41'", 0, test43);
	run_test("echo \\x41", 0, test44);
	run_test("echo \"$EMPTY\" unquoted-$EMPTY", 0, test45);
	run_test("cmd &&&&&&|| |||| &&&", 0, test46);
	run_test("echo 'test \"unterminated $VAR' >>file | cat << 'EOF' && echo fail || grep ok", 0, test47);
}

int main(void)
{
	run_lexer_tests();
	return (0);
}
