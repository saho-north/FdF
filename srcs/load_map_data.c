/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:43:47 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/22 18:53:43 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/**
 * Checks if the current string is a valid endptr.
 */
static bool	is_valid_endptr(char *str)
{
	if (str[0] == '\0' || (str[0] == '\n' && str[1] == '\0'))
	{
		return (true);
	}
	return (false);
}

/**
 * Checks if the given string is a valid hex color.
 * It must be in the format of ",0xRRGGBB".
 */
static bool	is_valid_color(char *str)
{
	size_t	index;

	if (str[0] != ',' || str[1] != '0' || str[2] != 'x')
	{
		return (false);
	}
	str += 3;
	index = 0;
	while (index < 6)
	{
		if (!ft_isxdigit(str[index]))
		{
			return (false);
		}
		index++;
	}
	printf("index: %zu\n", index);
	if (!is_valid_endptr(&str[index]))
	{
		return (false);
	}
	return (true);
}

/**
 * Parses the input of each point and stores the result in the struct.
 */
static bool	parse_point_input(char *point_input, t_fdf *fdf, size_t x, size_t y)
{
	t_atoi_res	res;

	res = ft_atoi_endptr(point_input);
	if (res.is_valid == false)
	{
		return (false);
	}
	set_point_values(fdf, x, y, res.num);
	if (is_valid_endptr(res.endptr))
	{
		set_default_color(&fdf->points[y][x]);
		return (true);
	}
	if (!is_valid_color(res.endptr))
	{
		return (false);
	}
	set_rgb_color(&fdf->points[y][x], res.endptr + 3);
	return (true);
}

/**
 * Parses the single line and stores the result in the struct.
 */
static void	parse_line(char *line, t_fdf *fdf, size_t y)
{
	char	**split_line;
	size_t	x;

	if (y >= fdf->max_y)
	{
		printf(" -> returning from parse_line at y: %zu\n", y);
		return ;
	}
	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		fdf->is_valid_map = false;
		return ;
	}
	x = 0;
	while (split_line[x] && x < fdf->max_x)
	{
		if (!parse_point_input(split_line[x], fdf, x, y))
		{
			printf("parse_point_input returned false for split_line[%zu]\n", x);
			printf("FAILED at split_line[%zu]: %s\n", x, split_line[x]);
			free_split_line(split_line);
			free(line);
			free_and_error_exit(fdf, ERR_MAP);
		}
		x++;
	}
	free_split_line(split_line);
}

/**
 * Loads the map data from the given file into the fdf struct.
 */
void	load_map_data(const char *filename, t_fdf *fdf)
{
	int			fd;
	size_t		y;
	t_gnl_res	res;

	//printf("max_x: %zu, max_y: %zu\n", fdf->max_x, fdf->max_y);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_and_perror_exit(fdf, ERR_FILE_OPEN);
	}
	y = 0;
	res.line_status = LINE_SUCCESS;
	while (res.line_status != LINE_EOF_REACHED)
	{
		res = get_next_line(fd);
		if (res.line_status == LINE_ERROR)
		{
			close(fd);
			free_and_error_exit(fdf, ERR_MAP);
		}
		// TODO: Later to delete
		//printf("line[%zu]: %s", y, res.line);
		parse_line(res.line, fdf, y);
		free(res.line);
		res.line = NULL;
		y++;
	}
	close(fd);
}
