/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:39:32 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/30 18:05:47 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_wrapper.h"

void	clean_shell(t_minishell *sh, int clean_env)
{
	if (!sh)
		return ;
	if (sh->env && clean_env)
	{
		env_free(sh->env);
		sh->env = NULL;
	}
	if (sh->token_list)
	{
		clean_token_list(sh->token_list);
		sh->token_list = NULL;
	}
	if (sh->ast)
	{
		free_ast(sh->ast);
		sh->ast = NULL;
	}
	if (sh->input)
	{
		free(sh->input);
		sh->input = NULL;
	}
}
