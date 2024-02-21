/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:25:32 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 16:27:34 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "usage.h"

/**
 * Put a pixel on the window.
 */
void	pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
	{
		return ;
	}
	dst = fdf->addr + (y * fdf->stride + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * Clear the image buffer to prepare for the next render.
 */
static void	clear_image(t_fdf *fdf)
{
	ft_bzero(fdf->addr, WIN_WIDTH * WIN_HEIGHT * fdf->bpp);
}

/**
 * Draw the usage on the window.
 */
static void	draw_usage(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	x = 20;
	y = 10;
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, TITLE_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, EXIT_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, RESET_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, PROJ_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, ZOOM_IN_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, ZOOM_OUT_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, MOVE_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, ROTATEX_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, ROTATEY_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, ROTATEZ_USAGE);
}

/**
 * Render the wireframe on the window after transforming the points.
 */
int	render(t_fdf *fdf)
{
	float	scale;
	float	z_scale;

	scale = fdf->scale;
	z_scale = scale / fdf->depth_scale;
	transform(fdf, scale, z_scale);
	clear_image(fdf);
	draw_wireframe(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	draw_usage(fdf);
	return (0);
}
