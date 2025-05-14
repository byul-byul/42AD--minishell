/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:35:16 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/14 21:04:19 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incls/minishell.h"

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
	char		*line;
	t_minishell	sh;

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
			(void)sh;
		}
		free(line);
	}
	return (0);
}
