/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:54:48 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/23 00:21:22 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/**
 * Counts the number of elements in a line split by spaces.
 * Used to determine the number of columns (max_x) in the map.
 */
static size_t	count_max_x(char *line)
{
	char	**split_line;
	char	**current;
	size_t	count;

	split_line = ft_split(line, ' ');
	if (!split_line)
	{
		return (0);
	}
	current = split_line;
	count = 0;
	while (*current)
	{
		if (**current != '\0' && **current != '\n')
		{
			count++;
		}
		free(*current);
		current++;
	}
	free(split_line);
	return (count);
}

/**
 * Counts the number of valid lines in the file, using the count_max_x function
 * to ensure each line has the same number of elements.
 * Used to determine the number of rows (max_y) in the map.
 */
static size_t	count_max_y(t_gnl_res res, size_t max_x, int fd)
{
	size_t	index;

	index = 0;
	while (res.line && res.line_status != LINE_ERROR)
	{
		if (res.line[0] == '\n' || res.line[0] == '\0')
		{
			free(res.line);
			break ;
		}
		if (count_max_x(res.line) > max_x)
		{
			printf("wrong length of line: %zu\n", index);
			printf("count_max_x(res.line): %zu\n", count_max_x(res.line));
			printf("max_x: %zu\n", max_x);
			free(res.line);
			return (0);
		}
		index++;
		free(res.line);
		res = get_next_line(fd);
	}
	if (res.line_status == LINE_ERROR)
	{
		free(res.line);
		return (0);
	}
	return (index);
}

/**
 * Determines the size of the map by counting the number of rows and columns.
 * Opens the file, reads lines using get_next_line, and uses count_max_x and
 * count_max_y to set the max_x and max_y in the fdf structure.
 */
void	get_map_size(const char *filename, t_fdf *fdf)
{
	int			fd;
	t_gnl_res	res;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		free_and_perror_exit(fdf, ERR_FILE_OPEN);
	}
	res = get_next_line(fd);
	if (res.line_status == LINE_ERROR || res.line == NULL)
	{
		close(fd);
		free_and_error_exit(fdf, ERR_READ_LINE);
	}
	fdf->max_x = count_max_x(res.line);
	fdf->max_y = count_max_y(res, fdf->max_x, fd);
	close(fd);
	if (fdf->max_x == 0 || fdf->max_y == 0)
	{
		free_and_error_exit(fdf, ERR_MAP);
	}
}
