/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:43:47 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/20 02:43:51 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/**
 * Parses the single line and stores the result in the struct.
 */
// static void	parse_line(char *line, t_fdf *fdf, size_t y)
// {
// 	char	**split_line;
// 	size_t	x;

// 	printf("parse_line[%zu] %s\n", y, line);
// 	split_line = ft_split(line, ' ');
// 	if (!split_line)
// 	{
// 		printf("ft_split returned NULL\n");
// 		free(line);
// 		free_and_perror_exit(fdf, ERR_MAP);
// 	}
// 	x = 0;
// 	while (split_line[x] && x < fdf->max_x)
// 	{
// 		printf("split_line[%zu]: %s\n", x, split_line[x]);
// 		if (!parse_point_input(split_line[x], fdf, x, y))
// 		{
// 			printf("parse_point_input returned false\n");
// 			free_split_line(split_line);
// 			free(line);
// 			free_and_error_exit(fdf, ERR_MAP);
// 		}
// 		x++;
// 	}
// 	printf("x: %zu, y: %zu\n", x, y);
// 	free_split_line(split_line);
// }

/**
 * Loads the map data from the given file into the fdf struct.
 */
void	load_map_data(const char *filename, t_fdf *fdf)
{
	int			fd;
	size_t		y;
	t_gnl_res	res;

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
		if (res.line_status == LINE_ERROR || !res.line)
		{
			close(fd);
			free_and_error_exit(fdf, ERR_MAP);
		}
		// if (y < fdf->max_y)
		// 	parse_line(res.line, fdf, y);
		free(res.line);
		res.line = NULL;
		y++;
	}
	close(fd);
}
