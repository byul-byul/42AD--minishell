/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:32:30 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/20 15:50:54 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"

extern volatile sig_atomic_t	g_sigint;

void	setup_child_signals(void);
void	setup_shell_signals(void);
void	sigint_handler(int sig);

#endif