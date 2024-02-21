/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:08:48 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 12:35:18 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

/**
 * Initializes the mlx environment for graphics rendering.
 */
static void	init_mlx_env(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		print_error_exit(ERR_FDF_INIT);
	}
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!fdf->win)
	{
		free_and_error_exit(fdf, ERR_FDF_INIT);
	}
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
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
 * Initializes the point struct with default values.
 */
static void	init_point_row(t_point *point, int max_x, int current_y)
{
	int	current_x;

	current_x = 0;
	while (current_x < max_x)
	{
		point[current_x].original_x = current_x;
		point[current_x].original_y = current_y;
		point[current_x].color = WHITE;
		point[current_x].is_exist = false;
		current_x++;
	}
}

/**
 * Initializes the 2D array of points that will be used to store the map.
 */
static void	init_point_matrix(t_fdf *fdf)
{
	int	y;

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
		init_point_row(fdf->points[y], fdf->max_x, y);
		y++;
	}
}

/**
 * Initializes the fdf struct with default values.
 */
// TODO: Check if all the values correctly initialized
/*
// TODO: Later to delete the debug printf
	printf("Initial scale: %f\n", fdf->scale);
	printf("Initial depth scale: %f\n", fdf->depth_scale);
	printf("Initial scale / depth scale: %f\n", fdf->scale / fdf->depth_scale);
	printf("Initial x_move: %d\n", fdf->x_move);
	printf("Initial y_move: %d\n", fdf->y_move);
	fdf->max_z = INT_MIN; // TODO: これはなんのために？
	fdf->min_z = INT_MAX; // TODO: これはなんのために？
 */
void	init_fdf(t_fdf *fdf, const char *filename)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	init_mlx_env(fdf);
	get_map_size(fdf, filename);
	init_point_matrix(fdf);
	fdf->max_z = INT_MIN;
	fdf->min_z = INT_MAX;
	fdf->projection = ISOMETRIC;
	reset_render_param(fdf);
}
