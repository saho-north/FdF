/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_height.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:54:48 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/22 20:01:18 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/**
 *
 */

void	get_map_height(const char *filename, t_fdf *fdf)
{
	int			fd;
	t_gnl_res	res;
	size_t		index;
	size_t		count;

	// TODO: Later to delete dubug printf in this function
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_and_perror_exit(fdf, ERR_FILE_OPEN);
	}
	ft_memset(&res, 0, sizeof(t_gnl_res));
	printf("INIT res.line: %s\n", res.line);
	printf("INIT res.line_status: %d\n", res.line_status);
	res.line_status = LINE_SUCCESS;
	index = 0;
	count = 0;
	while (res.line_status != LINE_EOF_REACHED)
	{
		res = get_next_line(fd);
		printf("line_status: %d\n", res.line_status);
		if (res.line == NULL)
		{
			printf("----------------------------------res.line is NULL\n");
			continue ;
		}
		printf("line[%zu]: %s", index, res.line);
		if (res.line_status == LINE_ERROR)
		{
			close(fd);
			free_and_error_exit(fdf, ERR_MAP);
		}
		if (res.line[0] != '\n' && res.line[0] != '\0')
		{
			count++;
		}
		index++;
		printf("count: %zu\n\n", count);
		free(res.line);
		res.line = NULL;
	}
	close(fd);
	fdf->max_y = count;
	if (fdf->max_y == 0)
	{
		free_and_error_exit(fdf, ERR_MAP);
	}
}
