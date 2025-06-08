/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 02:54:57 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/04 15:31:33 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_wrapper.h"

int	is_quoting(int c)
{
	return (c == '\'' || c == '"');
}

int	is_operator_char(int c)
{
	return (c == '|' || c == '<' || c == '>' || c == '&');
}

int	is_subshell_paren(int c)
{
	return (c == '(' || c == ')');
}

int	is_metachar(int c)
{
	return (is_subshell_paren(c) || is_operator_char(c));
}

int	is_dollar_sign(int c)
{
	return (c == '$');
}
