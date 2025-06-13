/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:13:03 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/14 02:46:42 by bhajili          ###   ########.fr       */
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
}			t_token_type;

typedef enum e_quote_type
{
	NONE,
	SINGLE,
	DOUBLE
}			t_quote_type;

typedef struct s_token
{
	int				error;
	char			*value;
	t_token_type	type;
	t_quote_type	quoted;
	int				heredoc_expand;
	int				expanded;
	struct s_token	*next;
}				t_token;

t_token	*lexer(char *input, int exit_status);
t_token	*fetch_token(char **input, int exit_status);
void	extract_token_value(char **input, t_token *token);
int		is_metachar(int c);
int		is_subshell_paren(int c);
int		is_operator_char(int c);
int		is_heredoc_expand(t_token *prev, t_quote_type quote_type);
void	clean_token_list(t_token *token_list);
char	*expand_token_value(const char *value, t_quote_type quoted,
		int last_exit_status);

#endif
