/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:47:30 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/23 03:49:52 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

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
 * Initializes the fdf struct with default values.
 */

static void	init_fdf_struct(t_fdf *fdf)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	fdf->max_z = INT_MIN;
	fdf->min_z = INT_MAX;
	fdf->is_valid_map = true;
}

/**
 * Initializes the mlx environment for graphics rendering.
 */
static void	init_mlx_env(t_fdf *fdf)
{
	fdf->xvar = mlx_init();
	if (!fdf->xvar)
	{
		print_error_exit(ERR_FDF_INIT);
	}
	fdf->window = mlx_new_window(fdf->xvar, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->window)
	{
		free_and_error_exit(fdf, ERR_FDF_INIT);
	}
	fdf->img = mlx_new_image(fdf->xvar, WIN_WIDTH, WIN_HEIGHT);
	if (!fdf->img)
	{
		free_and_error_exit(fdf, ERR_FDF_INIT);
	}
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp, &fdf->stride,
			&fdf->endian);
	if (!fdf->addr)
	{
		free_and_error_exit(fdf, ERR_FDF_INIT);
	}
}

/**
 * Initializes the 2D array of points that will be used to store the map.
 */
static void	init_point_matrix(t_fdf *fdf)
{
	size_t	y;

	fdf->points = (t_point **)ft_calloc(fdf->max_y, sizeof(t_point *));
	if (!fdf->points)
	{
		free_and_perror_exit(fdf, ERR_MALLOC);
	}
	y = 0;
	while (y < fdf->max_y)
	{
		fdf->points[y] = (t_point *)ft_calloc(fdf->max_x, sizeof(t_point));
		if (!fdf->points[y])
		{
			free_mlx_ptr(fdf);
			free_point_matrix(fdf->points, y);
			print_error_exit(ERR_MALLOC);
		}
		y++;
	}
}

/**
 * The main function of the program.
 * It checks the arguments and initializes the struct, mlx environment and map.
 * TODO: The function is not finished yet.
 * It will have more function calls to parse the map and render it.
 *
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
	printf("fdf.max_x: %zu, fdf.max_y: %zu\n", fdf.max_x, fdf.max_y);
	load_map_data(argv[1], &fdf);
	// TODO: parse the map and render it
	// if (!fdf.is_valid_map)
	// {
	// 	printf("fdf.is_valid_map: %d\n", fdf.is_valid_map);
	// 	free_and_error_exit(&fdf, ERR_MAP);
	// }
	free_mlx_ptr(&fdf);
	free_point_matrix(fdf.points, fdf.max_y);
	printf("-------------------------------------------------\n\n");
	//exit(EXIT_SUCCESS);
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
