/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:13:03 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/15 01:02:12 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define TRUE	1
# define FALSE	0
# define EXPAND_BUFFER_SIZE	1024
# define TOKEN_LIST_SIZE	256

# include <stdlib.h>
# include "libft.h"

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	LOGICAL_AND,
	LOGICAL_OR
}				t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	int				quoted;
	int				heredoc_expand;
	int				expanded;
	struct s_token	*next;
}				t_token;

t_token	*lexer(char *input, int exit_status);

#endif
