/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:35:16 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/15 00:59:31 by bhajili          ###   ########.fr       */
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
