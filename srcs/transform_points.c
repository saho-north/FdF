/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_points.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:59 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/02 16:19:10 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * Set the default line length for the points.
 * The length is determined by the window size and the number of points.
 */
void	set_default_line_len(t_fdf *fdf)
{
	float	x_len;
	float	y_len;
	float	default_len;
	size_t	x;
	size_t	y;

	x_len = (float)(WIN_WIDTH * 0.8) / (fdf->max_x - 1);
	y_len = (float)(WIN_HEIGHT * 0.8) / (fdf->max_y - 1);
	default_len = fmin(x_len, y_len);
	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			fdf->points[y][x].x += default_len * x;
			fdf->points[y][x].y += default_len * y;
			x++;
		}
		y++;
	}
}

/**
 * Move the points to the center of the window.
 */
void	move_to_center(t_fdf *fdf)
{
	size_t	x;
	size_t	y;
	float	center_x;
	float	center_y;
	float	x_offset;
	float	y_offset;

	center_x = (fdf->points[0][0].x + fdf->points[fdf->max_y - 1][fdf->max_x
			- 1].x) / 2;
	center_y = (fdf->points[0][0].y + fdf->points[fdf->max_y - 1][fdf->max_x
			- 1].y) / 2;
	x_offset = (float)WIN_WIDTH / 2 - center_x;
	y_offset = (float)WIN_HEIGHT / 2 - center_y;
	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			fdf->points[y][x].x += x_offset;
			fdf->points[y][x].y += y_offset;
			x++;
		}
		y++;
	}
}

/**
 * Apply isometric projection to each point.
 * The isometric projection is a type of axonometric projection.
 */
void	isometric_projection(t_point *point)
{
	point->x_2d = (point->x - point->y) * cos(30 * M_PI / 180);
	point->y_2d = (point->x + point->y) * sin(30 * M_PI / 180) - point->z;
}

/**
 * Apply isometric projection to all points.
 */
void	apply_isometric_projection(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			isometric_projection(&fdf->points[y][x]);
			x++;
		}
		y++;
	}
}

/**
 * Transform the points (x, y, z) to the 2D plane.
 * The function calls other functions to set the default line length,
 * move the points to the center of the window and apply isometric projection.
 */
void	transform_points(t_fdf *fdf)
{
	set_default_line_len(fdf);
	move_to_center(fdf);
	apply_isometric_projection(fdf);
}
