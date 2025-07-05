/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:32:30 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 04:05:29 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

extern volatile sig_atomic_t	g_exit_status;

void			setup_child_signals(void);
void			setup_shell_signals(void);
void			sigint_handler(int sig);
extern void		rl_replace_line(const char *text, int clear_undo);

#endif