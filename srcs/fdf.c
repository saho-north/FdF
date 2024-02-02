/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:47:30 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/02 16:14:22 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Checks if the given filename has the given extension.
 * It ignores the case of the filename and extension.
 */
static bool	check_file_extension(const char *filename, const char *extension)
{
	size_t	filename_len;
	size_t	extension_len;
	int		result;

	if (!filename || !extension)
	{
		return (false);
	}
	filename_len = ft_strlen(filename);
	extension_len = ft_strlen(extension);
	if (filename_len <= extension_len)
	{
		return (false);
	}
	result = ft_strcasecmp(&filename[filename_len - extension_len], extension);
	return (result == 0);
}

/**
 * Print out the points struct for debugging.
 * TODO: Delete this function later.
 */
static void	print_points(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	y = 0;
	printf("fdf.max_x: %zu, fdf.max_y: %zu\n", fdf->max_x, fdf->max_y);
	while (y < fdf->max_y)
	{
		x = 0;
		printf("point[%zu]: ", y);
		while (x < fdf->max_x)
		{
			printf("%d ", fdf->points[y][x].height);
			x++;
		}
		printf("\n");
		y++;
	}
}

/**
 * The main function of the program.
 * It checks the arguments and initializes the struct, mlx environment and map.
 * TODO: The function is not finished yet.
 * It will have more function calls to parse the map and render it.
 */
int	main(int argc, const char *argv[])
{
	t_fdf	fdf;

	printf("-------------------------------------------------\n");
	if (argc != 2 || !check_file_extension(argv[1], ".fdf"))
	{
		print_error_exit(ERR_ARG);
	}
	init_fdf_struct(&fdf);
	init_mlx_env(&fdf);
	get_map_size(argv[1], &fdf);
	init_point_matrix(&fdf);
	parse_map(argv[1], &fdf);
	print_points(&fdf); // TODO: Delete this function later.
	transform_points(&fdf);
	// TODO: parse the map and render it
	// mlx_key_hook(fdf.window, key_hook, &fdf);
	// mlx_hook(fdf.window, 17, 1L << 17, close_window, &fdf);
	// mlx_loop_hook(fdf.xvar, loop_hook, &fdf);
	mlx_loop(fdf.mlx_ptr);
	free_mlx_ptr(&fdf);
	free_point_matrix(fdf.points, fdf.max_y);
	return (0);
}

/**
 * The destructor function of the program.
 * It is used to check for memory leaks using the leaks command.
 * TODO: It will be deleted before the final submission.
 */

__attribute__((destructor)) static void destructor()
{
	system("leaks -q fdf");
}
