/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 12:25:32 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/18 02:35:49 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

static void	draw_usage(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	x = 20;
	y = 10;
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, "<< Usage >>");
	mlx_string_put(fdf->mlx, fdf->win, x, y += 20, WHITE, "EXIT: 'ESC' Key");
}

int	render(t_fdf *fdf)
{
	float	scale;
	float	z_scale;
	int		x_move;
	int		y_move;

	scale = fdf->scale;
	z_scale = scale / fdf->depth_scale;
	x_move = fdf->x_move;
	y_move = fdf->y_move;
	transform(fdf, scale, z_scale, x_move, y_move);
	draw_wireframe(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	draw_usage(fdf);
	fdf->needs_redraw = false;
	return (0);
}
