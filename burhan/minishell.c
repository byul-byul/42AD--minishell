/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:30:55 by bhajili           #+#    #+#             */
/*   Updated: 2025/03/10 13:00:11 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	show_tokens(t_token *head)
{
	while (head)
	{
		printf("type = %d: token = |%s|\n", head->type, head->value);
		head = head->next;
	}
}

void	minishell(void)
{
	char	*input;
	t_token	*tokens;

	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		tokens = lexer(input);
		// here will be token handler and command executor
		show_tokens(tokens); // just for testing
		free_tokens(tokens);
		free(input);
	}
}
