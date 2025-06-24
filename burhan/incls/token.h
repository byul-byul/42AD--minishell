/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:44:13 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/23 21:32:43 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

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
	LOGICAL_OR,
	OPEN_PAREN,
	CLOSE_PAREN
}			t_token_type;

typedef struct s_token
{
	int				error;
	char			*value;
	t_token_type	type;
	char			*quote_map;
	int				heredoc_expand;
	int				expanded;
	struct s_token	*next;
}				t_token;

t_token			*fetch_token(char **input);
void			init_token(t_token *token);
t_token_type	get_token_type(char *value, char *quote_map);
void			clean_token_list(t_token *token_list);
int				is_heredoc_expand(t_token *prev, const char *quote_map);
int				is_token_operator(int c);
int				is_meta_token(int c);
void			extract_token_value(char **input, t_token *token);

#endif