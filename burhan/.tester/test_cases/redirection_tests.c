/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_tests.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 05:25:38 by bhajili           #+#    #+#             */
/*   Updated: 2025/06/24 03:03:42 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tester.h"

const t_test_case redirection_tests[] =
{
	// REDIRECTION CASES
	{
		.input = "cat < input.txt",
		.expected_lexer = "WORD -> 'cat', REDIR_IN -> '<', WORD -> 'input.txt'",
		.expected_parser = "[CMD] cat < input.txt"
	},
	{
		.input = "echo hello > output.txt",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello', REDIR_OUT -> '>', WORD -> 'output.txt'",
		.expected_parser = "[CMD] echo hello > output.txt"
	},
	{
		.input = "echo hello >> output.txt",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello', APPEND -> '>>', WORD -> 'output.txt'",
		.expected_parser = "[CMD] echo hello >> output.txt"
	},
	{
		.input = "cat << EOF",
		.expected_lexer = "WORD -> 'cat', HEREDOC -> '<<', WORD -> 'EOF'",
		.expected_parser = "[CMD] cat << EOF"
	},
	{
		.input = "cat<file",
		.expected_lexer = "WORD -> 'cat', REDIR_IN -> '<', WORD -> 'file'",
		.expected_parser = "[CMD] cat < file"
	},
	{
		.input = "cat>file",
		.expected_lexer = "WORD -> 'cat', REDIR_OUT -> '>', WORD -> 'file'",
		.expected_parser = "[CMD] cat > file"
	},
	{
		.input = "cat>>file",
		.expected_lexer = "WORD -> 'cat', APPEND -> '>>', WORD -> 'file'",
		.expected_parser = "[CMD] cat >> file"
	},
	{
		.input = "cat<<EOF",
		.expected_lexer = "WORD -> 'cat', HEREDOC -> '<<', WORD -> 'EOF'",
		.expected_parser = "[CMD] cat << EOF"
	},
	{
		.input = "cat <   input.txt",
		.expected_lexer = "WORD -> 'cat', REDIR_IN -> '<', WORD -> 'input.txt'",
		.expected_parser = "[CMD] cat < input.txt"
	},
	{
		.input = "echo hello >   file",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello', REDIR_OUT -> '>', WORD -> 'file'",
		.expected_parser = "[CMD] echo hello > file"
	},
	{
		.input = "echo > file hello",
		.expected_lexer = "WORD -> 'echo', REDIR_OUT -> '>', WORD -> 'file', WORD -> 'hello'",
		.expected_parser = "[CMD] echo > file hello"
	},
	{
		.input = "echo hello>file",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello', REDIR_OUT -> '>', WORD -> 'file'",
		.expected_parser = "[CMD] echo hello > file"
	},
	{
		.input = "echo >>file",
		.expected_lexer = "WORD -> 'echo', APPEND -> '>>', WORD -> 'file'",
		.expected_parser = "[CMD] echo >> file"
	},
	{
		.input = "cat <<EOF | grep hi",
		.expected_lexer = "WORD -> 'cat', HEREDOC -> '<<', WORD -> 'EOF', PIPE -> '|', WORD -> 'grep', WORD -> 'hi'",
		.expected_parser = "[CMD] cat << EOF | grep hi"
	},
	// REDIRECTION CASES (robust and aggressive)
	{
		.input = "echo hello > output.txt",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello', REDIR_OUT -> '>', WORD -> 'output.txt'",
		.expected_parser = "[CMD] echo hello > output.txt"
	},
	{
		.input = "echo hello>file",
		.expected_lexer = "WORD -> 'echo', WORD -> 'hello', REDIR_OUT -> '>', WORD -> 'file'",
		.expected_parser = "[CMD] echo hello > file"
	},
	{
		.input = "echo > file hello",
		.expected_lexer = "WORD -> 'echo', REDIR_OUT -> '>', WORD -> 'file', WORD -> 'hello'",
		.expected_parser = "[CMD] echo > file hello"
	},
	{
		.input = "echo>   'file with spaces'",
		.expected_lexer = "WORD -> 'echo', REDIR_OUT -> '>', WORD -> 'file with spaces'",
		.expected_parser = "[CMD] echo > 'file with spaces'"
	},
	{
		.input = "cat<file",
		.expected_lexer = "WORD -> 'cat', REDIR_IN -> '<', WORD -> 'file'",
		.expected_parser = "[CMD] cat < file"
	},
	{
		.input = "cat <   input.txt",
		.expected_lexer = "WORD -> 'cat', REDIR_IN -> '<', WORD -> 'input.txt'",
		.expected_parser = "[CMD] cat < input.txt"
	},
	{
		.input = "echo >>file",
		.expected_lexer = "WORD -> 'echo', APPEND -> '>>', WORD -> 'file'",
		.expected_parser = "[CMD] echo >> file"
	},
	{
		.input = "cat >\"quoted.txt\"",
		.expected_lexer = "WORD -> 'cat', REDIR_OUT -> '>', WORD -> 'quoted.txt'",
		.expected_parser = "[CMD] cat > \"quoted.txt\""
	},
	{
		.input = "cat > ''",
		.expected_lexer = "WORD -> 'cat', REDIR_OUT -> '>', WORD -> ''",
		.expected_parser = "[CMD] cat > ''"
	},
	{
		.input = "cat > '$FILE'",
		.expected_lexer = "WORD -> 'cat', REDIR_OUT -> '>', WORD -> '$FILE'",
		.expected_parser = "[CMD] cat > '$FILE'"
	},
	{
		.input = "cat > $FILE",
		.expected_lexer = "WORD -> 'cat', REDIR_OUT -> '>', WORD -> '$FILE'",
		.expected_parser = "[CMD] cat > $FILE"
	},
	{
		.input = "cat < \"in.txt\" > 'out.txt'",
		.expected_lexer = "WORD -> 'cat', REDIR_IN -> '<', WORD -> 'in.txt', REDIR_OUT -> '>', WORD -> 'out.txt'",
		.expected_parser = "[CMD] cat < \"in.txt\" > 'out.txt'"
	},
	{
		.input = "echo >",
		.expected_lexer = "WORD -> 'echo', REDIR_OUT -> '>'",
		.expected_parser = "NULL"
	},
	{
		.input = "echo > > file",
		.expected_lexer = "WORD -> 'echo', REDIR_OUT -> '>', REDIR_OUT -> '>', WORD -> 'file'",
		.expected_parser = "NULL"
	}
};

const t_test_block redirection_block = {
	.block_name = "REDIRECTION TESTS",
	.block_label = "redirect",
	.cases = redirection_tests,
	.count = sizeof(redirection_tests) / sizeof(redirection_tests[0])
};
