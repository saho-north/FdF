/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:08:48 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/17 01:48:36 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

/**
 * Initializes the mlx environment for graphics rendering.
 */
static void	init_mlx_env(t_fdf *fdf, char *filename)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
	{
		free_and_error_exit(fdf, ERR_FDF_INIT);
	}
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, filename);
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
			ft_free2d((void **)fdf->points, y);
			print_error_exit(ERR_MALLOC);
		}
		init_point_row(fdf->points[y], fdf->max_x, y);
		y++;
	}
}

/**
 * Initializes the depth buffer for z-buffering.
 */
static double	**init_depth_buffer(t_fdf *fdf)
{
	double	**depth_buffer;

	depth_buffer = (double **)ft_alloc2d(WIN_HEIGHT, WIN_WIDTH, sizeof(double));
	if (!depth_buffer)
	{
		free_and_perror_exit(fdf, ERR_MALLOC);
	}
	return (depth_buffer);
}

/**
 * Initializes the fdf struct with default values.
 */
t_fdf	*init_fdf(const char *filename)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)ft_calloc(1, sizeof(t_fdf));
	if (!fdf)
	{
		perror_exit(ERR_MALLOC);
	}
	fdf->max_z = INT_MIN;
	fdf->min_z = INT_MAX;
	fdf->depth_buffer = init_depth_buffer(fdf);
	init_mlx_env(fdf, (char *)filename);
	get_map_size(fdf, filename);
	init_point_matrix(fdf);
	parse_map(fdf, filename);
	reset_render_param(fdf);
	return (fdf);
}
