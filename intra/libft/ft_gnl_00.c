/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhajili <bhajili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:49 by bhajili           #+#    #+#             */
/*   Updated: 2024/12/28 20:03:03 by bhajili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strjoin2(const char *s1, const char *s2)
{
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;
	char	*res;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	res = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (j < s1_len)
		res[i++] = s1[j++];
	j = 0;
	while (j < s2_len)
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

static void	clean_buff(char **buff)
{
	size_t	sublen;
	char	*cleaned;
	char	*pos;

	pos = ft_strchr(*buff, SEPARATOR);
	if (!pos)
	{
		free(*buff);
		*buff = NULL;
		return ;
	}
	sublen = pos - *buff + 1;
	if ((*buff)[sublen] == '\0')
	{
		free(*buff);
		*buff = NULL;
		return ;
	}
	cleaned = ft_substr(*buff, sublen, ft_strlen(pos));
	free (*buff);
	*buff = cleaned;
}

static char	*form_next_line(char *buff)
{
	size_t	len;
	char	*pos;

	pos = ft_strchr(buff, SEPARATOR);
	if (pos)
		len = pos - buff + 1;
	else
		len = ft_strlen(buff);
	return (ft_substr(buff, 0, len));
}

static char	*read_next_line(char *line, int fd)
{
	char	*buff;
	char	*tmp;
	int		read_bytes;

	read_bytes = 1;
	buff = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buff)
		return (free(line), line = NULL, NULL);
	buff[0] = '\0';
	while (read_bytes > 0 && !ft_strchr(line, SEPARATOR))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes > 0)
		{
			buff[read_bytes] = '\0';
			tmp = line;
			line = ft_strjoin2(line, buff);
			free(tmp);
		}
	}
	free(buff);
	if (read_bytes < 0 || !line)
		return (free(line), line = NULL, NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0 || fd > MAX_FD)
		return (NULL);
	if (!buff[fd] || !ft_strchr(buff[fd], SEPARATOR))
		buff[fd] = read_next_line(buff[fd], fd);
	if (!buff[fd])
		return (NULL);
	line = form_next_line(buff[fd]);
	if (!line || ft_strlen(line) == 0)
		return (free(buff[fd]), buff[fd] = NULL, free(line), NULL);
	clean_buff(&(buff[fd]));
	return (line);
}
