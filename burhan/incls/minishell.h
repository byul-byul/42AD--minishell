/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:29:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/14 20:59:14 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_minishell
{
	char	**envp;
	int		exit_status;
}				t_minishell;

int	minishell(char **envp);

#endif
