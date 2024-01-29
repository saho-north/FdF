/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 04:08:48 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/26 23:44:59 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

/**
 * Initializes the fdf struct with default values.
 */
void	init_fdf_struct(t_fdf *fdf)
{
	ft_memset(fdf, 0, sizeof(t_fdf));
	fdf->max_z = INT_MIN;
	fdf->min_z = INT_MAX;
}

/**
 * Initializes the mlx environment for graphics rendering.
 */
void	init_mlx_env(t_fdf *fdf)
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
 * Initializes the point struct with default values.
 * TODO: 0xFFFFFF or 0xFFFFFFFF? Should I include alpha?
 */
static void	init_point_row(t_point *point, size_t max_x, size_t current_y)
{
	size_t	current_x;

	current_x = 0;
	while (current_x < max_x)
	{
		point->source_z = 0;
		point->x = (float)current_x;
		point->y = (float)current_y;
		point->z = 0;
		point->color = 0xFFFFFF;
		point->rgb[0] = 255;
		point->rgb[1] = 255;
		point->rgb[2] = 255;
		point->is_exist = false;
		current_x++;
	}
}

/**
 * Initializes the 2D array of points that will be used to store the map.
 */
void	init_point_matrix(t_fdf *fdf)
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
		init_point_row(fdf->points[y], fdf->max_x, y);
		y++;
	}
}
