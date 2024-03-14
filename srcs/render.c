/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:25:32 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/14 23:38:26 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

/**
 * Clear the z_buffer to prepare for the next render.
 */
static void	clear_depth_buffer(t_fdf *fdf)
{
	int	y;
	int	x;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			fdf->depth_buffer[y][x] = (double)INT_MIN;
			x++;
		}
		y++;
	}
}

/**
 * Clear the image buffer to prepare for the next render.
 */
static void	clear_image(t_fdf *fdf)
{
	int		y;
	char	*row_start;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		row_start = fdf->addr + (y * fdf->stride);
		ft_bzero(row_start, WIN_WIDTH * (fdf->bpp / 8));
		y++;
	}
}

/**
 * Render the wireframe on the window after transforming the points.
 */
int	render(t_fdf *fdf)
{
	double	scale;
	double	z_scale;

	scale = fdf->scale;
	z_scale = scale / fdf->depth_scale;
	transform(fdf, scale, z_scale);
	clear_depth_buffer(fdf);
	clear_image(fdf);
	draw_wireframe(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	draw_usage(fdf);
	return (0);
}
