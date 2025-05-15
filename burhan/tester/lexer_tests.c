/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tests.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:06:07 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/15 16:15:55 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "tester.h"
// #include "../incls/lexer.h" // потом подключим, когда напишем
// #include <stdio.h>
// #include <string.h>

// static void	test_case(const char *input, const char *expected[])
// {
// 	t_token *tokens = lexer((char *)input);
// 	int i = 0;

// 	printf("Test: \"%s\"\n", input);
// 	while (tokens && expected[i])
// 	{
// 		if (!tokens || strcmp(tokens->value, expected[i]) != 0)
// 			printf("❌ Fail: expected \"%s\", got \"%s\"\n", expected[i], tokens ? tokens->value : "(null)");
// 		else
// 			printf("✅ Ok: \"%s\"\n", expected[i]);
// 		tokens = tokens->next;
// 		i++;
// 	}
// 	if (tokens || expected[i])
// 		printf("❌ Fail: token count mismatch\n");
// 	printf("\n");
// }

// void	run_lexer_tests(void)
// {
// 	const char *test1[] = {"echo", "hello", NULL};
// 	test_case("echo hello", test1);

// 	// сюда будем добавлять новые тесты
// }

#include <stdio.h>
#include "../incls/minishell.h" // твой minishell.h
#include "../incls/lexer.h" // твой minishell.h

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

void	print_token(t_token *token)
{
	while (token)
	{
		printf(GREEN "value: %-15s" RESET " | "
			   YELLOW "type: %-12s" RESET " | "
			   "quoted: %d | heredoc_expand: %d | expanded: %d\n",
			token->value ? token->value : "(null)",
			g_token_names[token->type],
			token->quoted,
			token->heredoc_expand,
			token->expanded);
		token = token->next;
	}
}

void	run_test(const char *input, int exit_status)
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
	clean_token_list(token_list);
	printf("\n");
}

void	run_lexer_tests(void)
{
	// Базовые
	run_test("echo hello world", 0);
	run_test("ls -la | grep src", 0);
	run_test("cat < infile > outfile", 0);

	// Кавычки
	run_test("echo 'quoted text'", 0);
	run_test("echo \"quoted $HOME\"", 0);
	run_test("echo 'unclosed", 0); // syntax error

	// Переменные
	run_test("echo $HOME $?", 42);
	run_test("echo $UNSET_VAR", 0);

	// Heredoc
	run_test("cat << EOF", 0);
	run_test("cat << 'EOF'", 0);

	// Логические операторы
	run_test("make && make clean || echo fail", 0);

	// Пограничные случаи
	run_test("", 0);
	run_test("     ", 0);
	run_test("||| >>> <<< && ||", 0);

	// Смешанные кавычки
	run_test("echo \"'inner single'\"", 0);
	run_test("echo '\"inner double $HOME\"'", 0);
	run_test("echo 'single $HOME inside'", 0);

	// Экранированные кавычки (если поддерживаешь экранирование)
	run_test("echo \\\"escaped double\\\"", 0);
	run_test("echo \\\'escaped single\\\'", 0);

	// Последовательности $
	run_test("echo $ $ $", 0);
	run_test("echo $$", 0);
	run_test("echo $1abc", 0);
	run_test("echo $- $@ $*", 0);

	// Редиректы без файла
	run_test("echo >", 0);
	run_test("echo <", 0);

	// Без пробелов между метатокенами
	run_test("echo>file", 0);
	run_test("echo>>file", 0);
	run_test("echo<<EOF", 0);

	// Пустой heredoc limiter
	run_test("cat <<", 0);

	// Wildcards
	run_test("echo *", 0);
	run_test("ls src/*.c", 0);

	// Subshell (если бонусы)
	run_test("(echo hello)", 0);
	run_test("ls | (grep a && cat b) || echo fail", 0);

	// Комбинированные сложные команды
	run_test("echo \"$HOME\" 'literal' | grep -v 'pattern' >> output", 0);
	run_test("cat << EOF | grep \"$USER\" || echo 'fail'", 0);

	// Вложенные кавычки одного типа — ошибка
	run_test("echo 'this 'is' wrong'", 0);
	run_test("echo \"this \"is\" wrong\"", 0);

	// Незакрытая кавычка внутри heredoc лимитера
	run_test("cat << 'EOF", 0);
	run_test("cat << \"EOF", 0);

	// Heredoc без лимитера, но с метатокеном
	run_test("cat << | grep", 0);
	run_test("cat << && echo fail", 0);

	// Переменная с уродским названием
	run_test("echo $A_B_C_123_456_xXx", 0);

	// Бесконечные доллары
	run_test("echo $$$$$$$$$$", 0);

	// Лимитер heredoc совпадает с метатокеном
	run_test("cat << |", 0);
	run_test("cat << &&", 0);

	// Скобки в скобках
	run_test("((()))", 0);
	run_test("echo ((hello))", 0);

	// Редирект сразу перед пайпом
	run_test("echo >| file", 0);
	run_test("echo >>| grep", 0);

	// Странные символы / escape-последовательности
	run_test("echo $'\\x41'", 0);
	run_test("echo \\x41", 0);

	// Пустая переменная в кавычках и без
	run_test("echo \"$EMPTY\" unquoted-$EMPTY", 0);

	// Бесконечная цепь логических операторов
	run_test("cmd &&&&&&|| |||| &&&", 0);

	// КРАШ-ТЕСТ: всё в одной строке
	run_test("echo 'test \"unterminated $VAR' >>file | cat << 'EOF' && echo fail || grep ok", 0);
}
