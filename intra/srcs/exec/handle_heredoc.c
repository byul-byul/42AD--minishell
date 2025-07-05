/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 16:27:10 by bhajili           #+#    #+#             */
/*   Updated: 2025/07/02 16:46:15 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_wrapper.h"

static int	is_heredoc_delimiter(const char *line, ssize_t len,
				const char *limiter)
{
	if (!line)
		return (1);
	if (len > 0 && line[len - 1] == '\n'
		&& !ft_strncmp(line, limiter, len - 1)
		&& limiter[len - 1] == '\0')
		return (1);
	return (0);
}

static int	write_line_to_pipe(char *line, int write_fd)
{
	ssize_t	len;

	len = ft_strlen(line);
	if (write(write_fd, line, len) == -1)
	{
		free(line);
		perror("write");
		return (1);
	}
	free(line);
	return (0);
}

static int	write_heredoc(t_redir *redir)
{
	int		pipefd[2];
	char	*line;

	if (pipe(pipefd) == -1)
		return (perror("pipe"), 1);
	while (TRUE)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(0);
		if (!line || is_heredoc_delimiter(line, ft_strlen(line),
				redir->filename))
			break ;
		if (write_line_to_pipe(line, pipefd[1]))
			return (close(pipefd[0]), close(pipefd[1]), 1);
	}
	free(line);
	close(pipefd[1]);
	redir->fd = pipefd[0];
	return (0);
}

int	handle_heredocs(t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redirections;
	while (redir)
	{
		if (redir->type == HEREDOC)
			if (write_heredoc(redir))
				return (1);
		redir = redir->next;
	}
	return (0);
}
