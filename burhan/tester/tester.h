/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:01:19 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/14 05:25:11 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

typedef struct s_test_case
{
	const char *input;
	const char *expected_lexer;
	const char *expected_parser;
}				t_test_case;

typedef struct s_test_block
{
	const char *block_name;
	const t_test_case *cases;
	int count;
}				t_test_block;

#endif