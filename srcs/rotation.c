/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:23:47 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/15 16:07:09 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/**
 * Rotates the given point around the X-axis.
 */
static void	rotate_x(t_point *point, float radians)
{
	float	original_y;

	original_y = point->y;
	point->y = original_y * cos(radians) - point->z * sin(radians);
	point->z = original_y * sin(radians) + point->z * cos(radians);
}

/**
 * Rotates the given point around the Y-axis.
 */
static void	rotate_y(t_point *point, float radians)
{
	float	original_x;

	original_x = point->x;
	point->x = original_x * cos(radians) + point->z * sin(radians);
	point->z = -original_x * sin(radians) + point->z * cos(radians);
}

/**
 * Rotates the given point around the Z-axis.
 */
static void	rotate_z(t_point *point, float radians)
{
	float	original_x;
	float	original_y;

	original_x = point->x;
	original_y = point->y;
	point->x = original_x * cos(radians) - original_y * sin(radians);
	point->y = original_x * sin(radians) + original_y * cos(radians);
}

/**
 * Rotates the map around the X, Y and Z axes.
*/
void	rotation(t_fdf *fdf, t_point *point)
{
	rotate_x(point, deg_to_rad(fdf->x_degree));
	rotate_y(point, deg_to_rad(fdf->y_degree));
	rotate_z(point, deg_to_rad(fdf->z_degree));
}
