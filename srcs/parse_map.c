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
 * Parses the single line and stores the result in the struct.
 * Returns false if an error occurs during the process.
 */
static bool	parse_line(char *line, t_fdf *fdf, size_t y)
{
	char	**split_line;
	size_t	x;

	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		return (false);
	}
	x = 0;
	while (split_line[x] && x < fdf->max_x)
	{
		if (!parse_point(fdf, &fdf->points[y][x], split_line[x]))
		{
			free_split_line(split_line);
			return (false);
		}
		x++;
	}
	free_split_line(split_line);
	return (true);
}

/**
 * Processes the map file and stores the result in the struct.
 * Exits the program if an error occurs during the process.
 */
void	parse_map(const char *filename, t_fdf *fdf)
{
	int			fd;
	t_gnl_res	res;
	size_t		y;
	bool		is_valid_map;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		free_and_perror_exit(fdf, ERR_FILE_OPEN);
	is_valid_map = true;
	y = 0;
	while (true)
	{
		res = get_next_line(fd);
		if (!res.line || res.line_status == LINE_ERROR)
			break ;
		if (y < fdf->max_y && !parse_line(res.line, fdf, y))
			is_valid_map = false;
		free(res.line);
		res.line = NULL;
		y++;
	}
	close(fd);
	if (!is_valid_map || res.line_status == LINE_ERROR)
		free_and_error_exit(fdf, ERR_MAP);
}
