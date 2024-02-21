/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:59 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 16:25:26 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * Scale the point based on the scale and z_scale values.
 */
static void	scaling(t_point *point, float scale, float z_scale)
{
	point->x = (float)point->original_x * scale;
	point->y = (float)point->original_y * scale;
	point->z = (float)point->original_z * z_scale;
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
void	transform(t_fdf *fdf, float scale, float z_scale)
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
		while (x < fdf->max_x && fdf->points[y][x].is_exist)
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
