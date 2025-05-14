/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 09:10:19 by bhajili           #+#    #+#             */
/*   Updated: 2025/05/12 17:22:40 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_tokens(t_token *tokens)
{
	t_token	*temp;

	while (tokens)
	{
		temp = tokens->next;
		free(tokens->value);
		free(tokens);
		tokens = temp;
	}
}

void	add_token(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!head || !new_token)
		return ;
	if (!*head)
	{
		*head = new_token;
		return ;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

int	identify_token_type(const char *value)
{
	if (!value)
		return (0);
	if (!ft_strcmp(value, "|"))
		return (PIPE);
	if (!ft_strcmp(value, "<"))
		return (REDIR_IN);
	if (!ft_strcmp(value, ">"))
		return (REDIR_OUT);
	if (!ft_strcmp(value, "<<"))
		return (HEREDOC);
	if (!ft_strcmp(value, ">>"))
		return (APPEND);
	if (!ft_strcmp(value, "&&"))
		return (LOGICAL_AND);
	if (!ft_strcmp(value, "||"))
		return (LOGICAL_OR);
	return (0);
}

int	is_operator(char c)
{
	return (c == '|' || c == '&' || c == '<' || c == '>');
}

void	define_token(const char *input, int *i)
{
	char	quote;

	quote = 0;
	while (input[*i] && (quote || (!is_operator(input[*i]) && input[*i] != ' ')))
	{
		if (input[*i] == '\\' && input[*i + 1] && quote != '\'')
		{
			(*i) += 2; // Пропускаем `\`, только если вне кавычек или внутри двойных
			continue ;
		}
		else if (!quote && (input[*i] == '"' || input[*i] == '\''))
			quote = input[*i]; // Открываем кавычки
		else if (quote && input[*i] == quote)
			quote = 0; // Закрываем кавычки
		(*i)++;
	}
}

void	handle_operator(const char *input, int *i)
{
	if (is_operator(input[*i + 1]) && input[*i] == input[*i + 1])
		(*i) += 2;
	else
		(*i)++;
}

void	skip_spaces(const char *input, int *i)
{
	while (input[*i] && input[*i] == ' ')
		(*i)++;
}

// char	*process_token_value(const char *input, int start, int end)
// {
// 	char	quote = 0;
// 	int		i = start;
// 	int		j = 0;
// 	char	*result = malloc(end - start + 1);
// 	if (!result)
// 		return (NULL);
// 	while (i < end)
// 	{
// 		if (!quote && (input[i] == '"' || input[i] == '\''))
// 			quote = input[i++];
// 		else if (quote && input[i] == quote)
// 		{
// 			quote = 0;
// 			i++;
// 		}
// 		else if (input[i] == '\\' && input[i + 1] && quote != '\'')
// 		{
// 			i++;                     // пропускаем `\`
// 			result[j++] = input[i++]; // копируем следующий символ
// 		}
// 		else
// 			result[j++] = input[i++];
// 	}
// 	result[j] = '\0';
// 	return (result);
// }

char	*process_token_value(const char *input, int start, int end)
{
	int		i;
	int		j;
	char	quote;
	char	*result;

	i = start;
	j = 0;
	quote = 0;
	result = (char *)malloc(sizeof(char) * (end - start + 1));
	if (result)
	{
		while (i < end)
		{
			if (!quote && (input[i] == '"' || input[i] == '\''))
				quote = input[i];
			else if (quote && input[i] == quote)
				quote = 0;
			else if (input[i] == '\\' && input[i + 1] && quote != '\'')
				result[j++] = input[i + 1]; // копируем следующий символ
			else
				result[j++] = input[i];
			i++;
		}
		result[j] = '\0';
	}
	return (result);
}

// Обрабатывает переменную окружения после символа `$`
// Пример: $USER или $? → получает значение и добавляет к строке результата
static void	handle_dollar(const char *s, int *i, char **res, t_shell *sh)
{
	char	*name;
	char	*val;
	int		start;

	start = ++(*i); // пропускаем '$', начинаем считывание имени переменной
	if (s[start] == '?') // если это $?
		(*i)++;
	else
		while (ft_isalnum(s[*i]) || s[*i] == '_') // собираем имя переменной
			(*i)++;
	name = ft_substr(s, start, *i - start); // выделяем имя
	val = get_var_value(name, sh);         // получаем значение переменной
	*res = append_str(*res, val);          // добавляем к результату
	free(name);
	free(val);
}

// Подставляет переменные окружения в строку:
// - $VAR и $? заменяются значениями
// - внутри '...' переменные игнорируются
// - внутри "..." и вне кавычек — подставляются
char	*expand_variables(const char *s, t_shell *sh)
{
	char	*res;
	char	q;
	int		i;

	i = 0;
	q = 0;
	res = ft_strdup(""); // начинаем с пустой строки
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (!q && (s[i] == '\'' || s[i] == '"')) // открываем кавычки
			q = s[i++];
		else if (q && s[i] == q) // закрываем кавычки
			q = 0 + i++;
		else if (s[i] == '$' && s[i + 1] && q != '\'') // обрабатываем переменную
			handle_dollar(s, &i, &res, sh);
		else
			res = append_char(res, s[i++]); // просто добавляем символ
	}
	return (res);
}

t_token	*create_token(const char *input, int *i, t_shell *shell)
{
	t_token	*token;
	int		start;
	char	*raw;
	char	*expanded;

	skip_spaces(input, i);
	start = *i;
	if (is_operator(input[*i]))
		handle_operator(input, i);
	else
		define_token(input, i);
	raw = process_token_value(input, start, *i);
	expanded = expand_variables(raw, shell);
	free(raw);
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = expanded;
	token->type = identify_token_type(token->value);
	token->next = NULL;
	return (token);
}

t_token	*split_into_tokens(const char *input)
{
	int		i;
	t_token	*head;
	t_token	*new_token;

	i = 0;
	head = NULL;
	while (input[i])
	{
		new_token = create_token(input, &i);
		if (!new_token)
			return (free_tokens(head), NULL);
		add_token(&head, new_token);
	}
	return (head);
}

t_token	*lexer(const char *input)
{
	if (!input || !*input)
		return (NULL);
	return (split_into_tokens(input));
}
