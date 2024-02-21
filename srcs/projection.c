/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 15:41:08 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/21 16:28:05 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	isometric_projection(t_point *point)
{
	point->x_2d = (point->x - point->y) * cos(deg_to_rad(30));
	point->y_2d = (point->x + point->y) * sin(deg_to_rad(30)) - point->z;
}

static void	orthographic_projection(t_point *point)
{
	point->x_2d = point->x;
	point->y_2d = point->y;
}

static void	oblique_projection(t_point *point, float degrees)
{
	point->x_2d = point->x + point->z * cos(deg_to_rad(degrees));
	point->y_2d = point->y + point->z * sin(deg_to_rad(degrees));
}

static void	cavalier_projection(t_point *point, float depth_scale)
{
	point->x_2d = point->x + (point->z * depth_scale) * cos(deg_to_rad(45));
	point->y_2d = point->y + (point->z * depth_scale) * sin(deg_to_rad(45));
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
	else if (fdf->projection == OBLIQUE)
	{
		oblique_projection(point, 45);
	}
	else if (fdf->projection == CAVALIER)
	{
		cavalier_projection(point, fdf->depth_scale);
	}
}
