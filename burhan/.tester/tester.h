/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:01:19 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/23 13:45:04 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTER_H
# define TESTER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../incls/lexer.h"
#include "../incls/expander.h"
#include "../incls/parser.h"
#include "../incls/env.h"

#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define RESET   "\033[0m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

typedef struct s_test_case
{
	const char	*input;
	const char	*expected_lexer;
	const char	*expected_expander;
	const char	*expected_parser;
	const char	*expected_ast;
}				t_test_case;

typedef struct s_test_block
{
	const char			*block_name;
	const char			*block_label;
	const t_test_case	*cases;
	int					count;
}				t_test_block;

#endif