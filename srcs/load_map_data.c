/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 00:43:47 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/20 01:05:31 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

static void	parse_line(const char *line, t_fdf *fdf, size_t y)
{
	size_t	x;
	char	**split_line;

	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		//なんでここでmax_yではなくyを渡してfreeしていたのか？
		//free_point_matrix(fdf->points, y);
		free(line);
		free_and_perror_exit(fdf, ERR_MAP);
	}
	x = 0;
	while (split_line[x] && x < fdf->max_x)
	{
		if (!parse_point_input(split_line[x], fdf, x, y))
		{
			//これでいいかよくわからないから後でチェックする
			free_split_line(split_line);
			free(line);
			free_and_error_exit(fdf, ERR_MAP);
		}
		x++;
	}
	free_split_line(split_line);
}

void	load_map_data(const char *filename, t_fdf *fdf)
{
	t_gnl_res	res;
	int			fd;
	size_t		y;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_and_perror_exit(fdf, ERR_FILE_OPEN);
	}
	y = 0;
	while (y < fdf->max_y)
	{
		res = get_next_line(fd);
		if (res.line_status == LINE_ERROR || !res.line)
		{
			close(fd);
			free_and_perror_exit(fdf, ERR_MAP);
		}
		parse_line(res.line, fdf, y);
		free(res.line);
		res.line = NULL;
		y++;
	}
	close(fd);
}
