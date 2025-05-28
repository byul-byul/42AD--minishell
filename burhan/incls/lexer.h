/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:13:03 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/28 17:56:16 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "libft.h"

# define TRUE	1
# define FALSE	0

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	LOGICAL_AND,
	LOGICAL_OR,
	OPEN_PAREN,
	CLOSE_PAREN  
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
t_token	*fetch_token(char **input, t_token *prev_token, int exit_status);
void	extract_to_token(t_token *token, char **input);
char	*expand_token_value(const char *value, int last_exit_status);
int		is_metachar(char c);
void	clean_token_list(t_token *token_list);

#endif
