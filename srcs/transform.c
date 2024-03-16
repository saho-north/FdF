/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:59 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/16 21:22:53 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * Scale the point based on the scale and z_scale values.
 */
static void	scaling(t_point *point, double scale, double z_scale)
{
	point->x = (double)point->original_x * scale;
	point->y = (double)point->original_y * scale;
	point->z = (double)point->original_z * z_scale;
}

/**
 * Translates the point based on the x and y move values.
 */
static void	translate(t_point *point, int x_move, int y_move)
{
	point->x_2d += x_move;
	point->y_2d += y_move;
}

/**
 * transform the point to prepare for drawing
 */
void	transform(t_fdf *fdf, double scale, double z_scale)
{
	int	x;
	int	y;
	int	x_move;
	int	y_move;

	x_move = fdf->x_move;
	y_move = fdf->y_move;
	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			scaling(&fdf->points[y][x], scale, z_scale);
			rotation(fdf, &fdf->points[y][x]);
			projection(fdf, &fdf->points[y][x]);
			translate(&fdf->points[y][x], x_move, y_move);
			x++;
		}
		y++;
	}
}
