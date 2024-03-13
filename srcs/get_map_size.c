/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:54:48 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/13 23:20:40 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/**
 * Counts the number of point elements in the given line.
 * TODO: add error handling when founding continuous delimiter "1 2 3  4 5"
 */
static size_t	count_points_in_line(char *str, char delimiter)
{
	size_t	point_count;
	bool	is_point;

	if (!str)
	{
		return (0);
	}
	point_count = 0;
	is_point = false;
	while (*str)
	{
		if (!is_point && *str != delimiter && *str != '\n')
		{
			point_count++;
			is_point = true;
		}
		else if (is_point && *str == delimiter)
		{
			is_point = false;
		}
		str++;
	}
	return (point_count);
}

/**
 * Counts the number of rows and columns in the map.
 * The empty line is ignored.
 */
static void	count_lines(t_fdf *fdf, int fd)
{
	char	*line;
	bool	line_status;

	line = NULL;
	line_status = false;
	while (true)
	{
		line = get_next_line(fd, &line_status);
		if (!line_status)
		{
			close(fd);
			free_and_error_exit(fdf, ERR_READ_LINE);
		}
		if (!line)
		{
			return ;
		}
		if (fdf->max_x == 0)
		{
			fdf->max_x = count_points_in_line(line, ' ');
		}
		if (*line != '\n' && *line != '\0')
		{
			fdf->max_y++;
		}
		free(line);
	}
}

/**
 * Opens the file and counts the number of rows and columns in the map.
 * If the file cannot be opened or the map is empty, the program exits.
 */
void	get_map_size(t_fdf *fdf, const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_and_perror_exit(fdf, ERR_FILE_OPEN);
	}
	count_lines(fdf, fd);
	close(fd);
	if (fdf->max_x == 0 || fdf->max_y == 0)
	{
		free_and_error_exit(fdf, ERR_MAP);
	}
}
