/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 20:29:01 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/14 23:55:59 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "libft.h"
# include "lexer.h"

typedef struct s_minishell
{
	char	**envp;
	int		exit_status;
}				t_minishell;

int	minishell(char **envp);

#endif
