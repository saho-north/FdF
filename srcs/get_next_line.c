/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:06:36 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/23 17:32:29 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_buffered_text(char **buffered_text)
{
	free(*buffered_text);
	*buffered_text = NULL;
}

static char	*new_line_eof(char **buffered_text)
{
	char	*last_line;

	last_line = ft_strdup(*buffered_text);
	free_buffered_text(buffered_text);
	if (!last_line)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	return (last_line);
}

static char	*new_line_continue(char **buffered_text, char *marker)
{
	char	*next_line;
	char	*tmp;

	next_line = ft_substr(*buffered_text, 0, marker - *buffered_text + 1);
	if (!next_line)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	tmp = ft_strdup(marker + 1);
	if (!tmp)
	{
		perror("Memory allocation failed");
		free(next_line);
		return (NULL);
	}
	free_buffered_text(buffered_text);
	*buffered_text = tmp;
	return (next_line);
}

static char	*extract_next_line(char **buffered_text)
{
	char	*line;
	char	*marker;

	marker = ft_strchr(*buffered_text, '\n');
	if (marker)
	{
		line = new_line_continue(buffered_text, marker);
	}
	else
	{
		line = new_line_eof(buffered_text);
	}
	return (line);
}

static char	*strjoin_plus(char *buffered_text, char *read_buffer)
{
	char	*dst;
	size_t	len1;
	size_t	len2;

	if (!buffered_text || !read_buffer)
		return (NULL);
	len1 = ft_strlen(buffered_text);
	len2 = ft_strlen(read_buffer);
	dst = (char *)ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!dst)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	ft_memcpy(dst, buffered_text, len1);
	ft_memcpy(dst + len1, read_buffer, len2);
	free(buffered_text);
	buffered_text = NULL;
	return (dst);
}

static t_read_status	read_from_file(int fd, char **buffered_text)
{
	char	read_buffer[BUFFER_SIZE + 1];
	char	*tmp;
	ssize_t	bytes_read;

	while (!ft_strchr(*buffered_text, '\n'))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			perror("File read failed");
			return (READ_ERROR);
		}
		if (bytes_read == 0)
			return (READ_EOF);
		read_buffer[bytes_read] = '\0';
		tmp = strjoin_plus(*buffered_text, read_buffer);
		if (!tmp)
		{
			perror("Memory allocation failed");
			return (READ_ERROR);
		}
		*buffered_text = tmp;
	}
	return (READ_SUCCESS);
}

static t_read_status	init_buffered_text(char **buffered_text)
{
	if (!*buffered_text)
	{
		*buffered_text = (char *)ft_calloc(1, sizeof(char));
		if (!*buffered_text)
		{
			perror("Memory allocation failed");
			return (READ_ERROR);
		}
	}
	return (READ_SUCCESS);
}

char	*get_next_line(int fd)
{
	static char		*buffered_text;
	char			*line;
	t_read_status	read_status;

	if (fd < 0)
	{
		perror("File open failed");
		return (NULL);
	}
	read_status = init_buffered_text(&buffered_text);
	if (read_status == READ_ERROR)
		return (NULL);
	read_status = read_from_file(fd, &buffered_text);
	if (read_status == READ_ERROR || (read_status == READ_EOF
			&& ft_strlen(buffered_text) == 0))
	{
		free_buffered_text(&buffered_text);
		return (NULL);
	}
	line = extract_next_line(&buffered_text);
	if (!line)
		free_buffered_text(&buffered_text);
	return (line);
}
