/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:35:16 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/15 01:24:38 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/minishell.h"

void	show_tokens(t_token *head)
{
	while (head)
	{
		printf("type = %d: token = |%s|\n", head->type, head->value);
		head = head->next;
	}
}

static char	*read_input(void)
{
	char	*line;

	line = readline("");
	if (line && *line)
		add_history(line);
	return (line);
}

static void	display_prompt(void)
{
	printf("minishell$ ");
}

static int	init_minishell(t_minishell *sh, char **envp)
{
	sh->envp = envp;
	sh->exit_status = 0;
	return (0);
}

int	minishell(char **envp)
{
	t_minishell	sh;
	t_token		*token_list;
	char		*line;

	if (init_minishell(&sh, envp))
		return (1);
	while (1)
	{
		display_prompt();
		line = read_input();
		if (!line)
		{
			printf("exit\n");
			break ;
		}
		if (*line)
		{
			// здесь будет обработка строки (lexer, parser, executor)
			token_list = lexer(line, sh.exit_status);
			show_tokens(token_list);
			(void)sh;
		}
		free(line);
	}
	return (0);
}





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
}
