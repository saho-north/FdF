/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 21:39:27 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/14 21:41:28 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"
#include "usage.h"

/**
 * Draw the usage on the window.
 */
void	draw_usage(t_fdf *fdf)
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
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, DEPTH_USAGE);
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, COLOR_USAGE);
}
