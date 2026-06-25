/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eyagiz <eyagiz@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 12:23:55 by eyagiz            #+#    #+#             */
/*   Updated: 2026/06/25 20:34:37 by eyagiz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	has_newline(char *str)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static char	*extract_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash || *stash == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	line = malloc(i + 1 + (stash[i] == '\n'));
	if (!line)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*rebuild_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
	{
		free(stash);
		return (NULL);
	}
	new_stash = malloc(ft_strlen(stash) - i);
	if (!new_stash)
	{
		free(stash);
		return (NULL);
	}
	i++;
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

static char	*read_and_stash(int fd, char *stash)
{
	char	*buf;
	int		read_bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	read_bytes = 1;
	while (!has_newline(stash) && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			free(stash);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		stash = join_stash(stash, buf);
		if (!stash)
			break ;
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[10240];

	if (fd < 0 || fd >= 10240 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
	{
		stash[fd] = malloc(1);
		if (!stash[fd])
			return (NULL);
		stash[fd][0] = '\0';
	}
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = rebuild_stash(stash[fd]);
	return (line);
}
