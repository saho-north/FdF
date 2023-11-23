/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:06:36 by sakitaha          #+#    #+#             */
/*   Updated: 2023/11/24 00:56:22 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_eof(char **buffered_text)
{
	char	*last_line;

	last_line = ft_strdup(*buffered_text);
	free(*buffered_text);
	*buffered_text = NULL;
	if (!last_line)
	{
		perror("Memory allocation failed");
		return (NULL);
	}
	return (last_line);
}

static char	*line_continued(char **buffered_text, char *marker)
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
	free(*buffered_text);
	*buffered_text = tmp;
	return (next_line);
}

static t_read_status	extract_next_line(char **buffered_text, char **line)
{
	char	*marker;

	if (ft_strlen(*buffered_text) == 0)
	{
		*line = NULL;
		return (READ_EOF);
	}
	marker = ft_strchr(*buffered_text, '\n');
	if (marker)
	{
		*line = line_continued(buffered_text, marker);
		if (!*line)
		{
			perror("Memory allocation failed");
			return (READ_ERROR);
		}
		return (READ_SUCCESS);
	}
	*line = line_eof(buffered_text);
	if (!*line)
		return (READ_ERROR);
	return (READ_EOF);
}

static t_read_status	append_buffer(char **buffered_text, char *read_buffer)
{
	char	*tmp;

	tmp = ft_strjoin(*buffered_text, read_buffer);
	if (!tmp)
	{
		perror("Memory allocation failed");
		return (READ_ERROR);
	}
	free(*buffered_text);
	*buffered_text = tmp;
	return (READ_SUCCESS);
}

static t_read_status	read_from_file(int fd, char **buffered_text)
{
	char			read_buffer[BUFFER_SIZE + 1];
	ssize_t			bytes_read;
	t_read_status	read_status;

	while (!ft_strchr(*buffered_text, '\n'))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			perror("File read failed");
			return (READ_ERROR);
		}
		if (bytes_read == 0)
			break ;
		read_buffer[bytes_read] = '\0';
		read_status = append_buffer(buffered_text, read_buffer);
		if (read_status == READ_ERROR)
			return (READ_ERROR);
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

char	*get_next_line(int fd, t_read_status *read_status)
{
	static char	*buffered_text;
	char		*line;

	if (fd < 0)
	{
		perror("File open failed");
		*read_status = READ_ERROR;
		return (NULL);
	}
	*read_status = init_buffered_text(&buffered_text);
	if (*read_status == READ_ERROR)
		return (NULL);
	*read_status = read_from_file(fd, &buffered_text);
	if (*read_status == READ_ERROR)
	{
		free(buffered_text);
		return (NULL);
	}
	*read_status = extract_next_line(&buffered_text, &line);
	if (*read_status == READ_ERROR || *read_status == READ_EOF)
	{
		free(buffered_text);
	}
	return (line);
}
