/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:43:16 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/26 19:50:55 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_wrapper.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	return (run_minishell(envp));
}
