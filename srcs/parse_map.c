/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:43:47 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/26 23:47:40 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/**
 * Returns true if the character indicates the end of the line.
 */
static bool	is_eol(char c)
{
	return (c == '\0' || c == '\n');
}

/**
 * Parses the single line and stores the result in the struct.
 * Returns false if an error occurs during the process.
 */
static bool	parse_line(char *line, t_fdf *fdf, int y)
{
	char	**split_line;
	int		x;

	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		return (false);
	}
	x = 0;
	while (x < fdf->max_x && split_line[x] && !is_eol(split_line[x][0]))
	{
		if (!parse_point(fdf, &fdf->points[y][x], split_line[x]))
		{
			free_split_line(split_line);
			return (false);
		}
		x++;
	}
	if (split_line[x] && !is_eol(split_line[x][0]))
	{
		free_split_line(split_line);
		return (false);
	}
	free_split_line(split_line);
	return (true);
}

/**
 * Processes the map file and stores the result in the struct.
 * Exits the program if an error occurs during the process.
 */
void	parse_map(t_fdf *fdf, const char *filename)
{
	int		fd;
	int		processed_y;
	char	*line;
	bool	line_status;
	bool	is_valid_map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		free_and_perror_exit(fdf, ERR_FILE_OPEN);
	processed_y = 0;
	is_valid_map = true;
	while (true)
	{
		line = get_next_line(fd, &line_status);
		if (!line || !line_status)
			break ;
		if (processed_y < fdf->max_y && !parse_line(line, fdf, processed_y))
			is_valid_map = false;
		free(line);
		line = NULL;
		processed_y++;
	}
	close(fd);
	if (!line_status || !is_valid_map)
		free_and_error_exit(fdf, ERR_MAP);
}
