/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:54:48 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/15 17:03:58 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/**
 * Returns true if the character indicates the empty line.
 */
bool	is_empty_line(char *line)
{
	if (!line || *line == '\0')
	{
		return (true);
	}
	if (*line == '\n' && *(line + 1) == '\0')
	{
		return (true);
	}
	return (false);
}

/**
 * Counts the number of point elements in the given line.
 */
static int	count_points_in_line(char *str)
{
	int		point_count;
	bool	is_point;

	if (!str)
		return (0);
	point_count = 0;
	is_point = false;
	while (*str)
	{
		if (!is_point && *str != ' ' && *str != '\n')
		{
			point_count++;
			is_point = true;
		}
		else if (is_point && *str == ' ')
		{
			is_point = false;
		}
		str++;
	}
	return (point_count);
}

/**
 * Checks if the line format is valid.
 */
static bool	is_line_format_valid(char *str)
{
	bool	is_space;

	is_space = false;
	while (*str)
	{
		if (*str == ' ')
		{
			if (is_space)
			{
				return (false);
			}
			is_space = true;
		}
		else
		{
			is_space = false;
		}
		str++;
	}
	return (true);
}

static void	validate_line(t_fdf *fdf, char *line, bool *eom, bool *is_map_valid)
{
	int	counted_points;

	if (!is_map_valid || !is_line_format_valid(line))
	{
		*is_map_valid = false;
		return ;
	}
	counted_points = count_points_in_line(line);
	if (fdf->max_x == 0 && fdf->max_y == 0)
	{
		fdf->max_x = counted_points;
		if (fdf->max_x == 0)
			*is_map_valid = false;
	}
	if (*eom && !is_empty_line(line))
		*is_map_valid = false;
	else if (!*eom && is_empty_line(line))
		*eom = true;
	else if (!*eom && fdf->max_x != counted_points)
		*is_map_valid = false;
}

/**
 * Counts the number of rows and columns in the map.
 */
static void	count_lines(t_fdf *fdf, int fd, bool *is_map_valid)
{
	char	*line;
	bool	line_status;
	bool	end_of_map;

	line = NULL;
	line_status = false;
	end_of_map = false;
	while (true)
	{
		line = get_next_line(fd, &line_status);
		if (!line_status)
		{
			close(fd);
			free_and_error_exit(fdf, ERR_READ_LINE);
		}
		if (!line)
			return ;
		validate_line(fdf, line, &end_of_map, is_map_valid);
		if (!end_of_map && *is_map_valid)
			fdf->max_y++;
		free(line);
	}
}

/**
 * Opens the file and counts the number of rows and columns in the map.
 * If the file cannot be opened or the map is empty, the program exits.
 */
void	get_map_size(t_fdf *fdf, const char *filename)
{
	int		fd;
	bool	is_map_valid;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_and_perror_exit(fdf, ERR_FILE_OPEN);
	}
	is_map_valid = true;
	count_lines(fdf, fd, &is_map_valid);
	close(fd);
	if (fdf->max_x == 0 || fdf->max_y == 0 || !is_map_valid)
	{
		free_and_error_exit(fdf, ERR_MAP);
	}
}
