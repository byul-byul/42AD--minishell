/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 12:44:13 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/03 13:54:50 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# include "libft.h"
# include "signals.h"

# define C_RESET   "\033[0m"
# define C_BLUE    "\033[34m"
# define C_YELLOW  "\033[33m"
# define C_WHITE   "\033[37m"

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

// .quote_map:
// - has the same len as .value and filled by '0', '1' or '2'
// - '0' - no quouting; '1' - single quoting; '2' - double quoting
// - ex: .value = [echo "Hello" 'world']; .quote_map = [00000022222000111110]
typedef struct s_token
{
	char			*value;
	t_token_type	type;
	char			*quote_map;
	int				heredoc_expand;
	int				expanded;
	struct s_token	*next;
}				t_token;

t_token			*fetch_token(char **input);
t_token			*create_token(t_token_type type, const char *value);
void			tokenlist_push_back(t_token **head, t_token *new_token);
t_token_type	get_token_type(char *value, char *quote_map);
void			clean_token_list(t_token *token_list);
int				is_heredoc_expand(t_token *prev, const char *quote_map);
int				is_token_operator(int c);
int				is_meta_token(int c);
int				is_redirect_token(t_token_type type);
void			extract_token_value(char **input, t_token *token);
void			print_token_list(t_token *list);

#endif