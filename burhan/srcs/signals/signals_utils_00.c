/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils_00.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:36:20 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 10:49:18 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals_wrapper.h"

volatile sig_atomic_t	g_exit_status = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

// void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	g_exit_status = 130;
// }

void	sigquit_handler(int sig)
{
	(void)sig;
	g_exit_status = 131;
	write(STDOUT_FILENO, "Quit: 3\n", 8);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	setup_shell_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
