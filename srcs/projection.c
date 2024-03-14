/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:41:08 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/14 14:56:19 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	isometric_projection(t_point *point)
{
	double	radian;

	radian = deg_to_rad(ISO_DEGREE);
	point->x_2d = (point->x - point->y) * cos(radian);
	point->y_2d = (point->x + point->y) * sin(radian) - point->z;
}

static void	orthographic_projection(t_point *point)
{
	point->x_2d = point->x;
	point->y_2d = point->y;
}

static void	cabinet_projection(t_point *point)
{
	double	radian;

	radian = deg_to_rad(CABINET_DEGREE);
	point->x_2d = point->x + 0.5 * point->z * cos(radian);
	point->y_2d = point->y + 0.5 * point->z * sin(radian);
}

static void	trimetric_projection(t_point *point)
{
	double	angle_x;
	double	angle_y;
	double	angle_z;

	angle_x = deg_to_rad(TRIMETRIC_DEGREE_X);
	angle_y = deg_to_rad(TRIMETRIC_DEGREE_Y);
	angle_z = deg_to_rad(TRIMETRIC_DEGREE_Z);
	point->x_2d = point->x * cos(angle_x) - point->y * sin(angle_y);
	point->y_2d = point->x * sin(angle_x) + point->y * cos(angle_y) - point->z
		* sin(angle_z);
}

/**
 * Project the 3D point to 2D point based on the projection type.
 */
void	projection(t_fdf *fdf, t_point *point)
{
	if (fdf->projection == ISOMETRIC)
	{
		isometric_projection(point);
	}
	else if (fdf->projection == ORTHOGRAPHIC)
	{
		orthographic_projection(point);
	}
	else if (fdf->projection == CABINET)
	{
		cabinet_projection(point);
	}
	else if (fdf->projection == TRIMETRIC)
	{
		trimetric_projection(point);
	}
}
