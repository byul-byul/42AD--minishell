/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 00:13:03 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/14 20:12:12 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define EXPAND_BUFFER_SIZE	1024
# define TOKEN_LIST_SIZE	256

t_token	*lexer(char *input);

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
}				t_token;

#endif
