/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:30:55 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/12 23:46:12 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

void	show_tokens(t_token *head)
{
	while (head)
	{
		printf("type = %d: token = |%s|\n", head->type, head->value);
		head = head->next;
	}
}

t_env	*get_env_from_envp(char **envp)
{
	t_env	*head;
	t_env	*new;
	char	*equal;
	int		len;

	head = NULL;
	while (*envp)
	{
		equal = ft_strchr(*envp, '=');
		if (equal)
		{
			len = equal - *envp;
			new = malloc(sizeof(t_env));
			if (!new)
				return (NULL); // или free(head) и вернуть NULL
			new->key = ft_substr(*envp, 0, len);
			new->value = ft_strdup(equal + 1);
			new->next = head;
			head = new;
		}
		envp++;
	}
	return (head);
}

void	minishell(void)
{
	t_shell	shell;
	char	*input;
	t_token	*tokens;

	shell.env = get_env_from_envp(environ); // преобразуем char **environ → t_env *
	shell.last_exit = 0;
	shell.stdin_backup = dup(STDIN_FILENO);
	shell.stdout_backup = dup(STDOUT_FILENO);
	shell.is_interactive = isatty(STDIN_FILENO);

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		tokens = lexer(input, &shell);
		show_tokens(tokens); // для отладки
		free_tokens(tokens);
		free(input);
	}
}

// void	minishell(void)
// {
// 	char	*input;
// 	t_token	*tokens;

// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (!input)
// 			break ;
// 		tokens = lexer(input);
// 		// here will be token handler and command executor
// 		show_tokens(tokens); // just for testing
// 		free_tokens(tokens);
// 		free(input);
// 	}
// }
