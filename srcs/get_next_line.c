/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 23:06:36 by sakitaha          #+#    #+#             */
/*   Updated: 2023/12/20 23:03:28 by sakitaha         ###   ########.fr       */
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

static t_line_status	extract_next_line(char **buffered_text, char **line)
{
	char	*marker;

	if (ft_strlen(*buffered_text) == 0)
	{
		*line = NULL;
		return (LINE_EOF_REACHED);
	}
	marker = ft_strchr(*buffered_text, '\n');
	if (marker)
	{
		*line = line_continued(buffered_text, marker);
		if (!*line)
			return (LINE_ERROR);
		return (LINE_SUCCESS);
	}
	*line = line_eof(buffered_text);
	if (!*line)
		return (LINE_ERROR);
	return (LINE_EOF_REACHED);
}

static t_line_status	read_from_file(int fd, char **buffered_text)
{
	char	read_buffer[BUFFER_SIZE + 1];
	char	*tmp;
	ssize_t	bytes_read;

	while (!ft_strchr(*buffered_text, '\n'))
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (LINE_ERROR);
		if (bytes_read == 0)
			break ;
		read_buffer[bytes_read] = '\0';
		tmp = ft_strjoin(*buffered_text, read_buffer);
		if (!tmp)
			return (LINE_ERROR);
		free(*buffered_text);
		*buffered_text = tmp;
	}
	return (LINE_SUCCESS);
}

t_gnl_res	get_next_line(int fd)
{
	static char	*buffered_text;
	t_gnl_res	res;

	if (!buffered_text)
		buffered_text = (char *)ft_calloc(1, sizeof(char));
	if (!buffered_text || fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		free(buffered_text);
		res.line_status = LINE_ERROR;
		return (res);
	}
	res.line_status = read_from_file(fd, &buffered_text);
	if (res.line_status == LINE_ERROR)
	{
		free(buffered_text);
		return (res);
	}
	res.line_status = extract_next_line(&buffered_text, &res.line);
	if (res.line_status == LINE_ERROR || res.line_status == LINE_EOF_REACHED)
		free(buffered_text);
	return (res);
}
