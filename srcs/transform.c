/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:59 by sakitaha          #+#    #+#             */
/*   Updated: 2024/02/17 23:50:30 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	scaling(t_point *point, float scale, float z_scale)
{
	point->x = (float)point->original_x * scale;
	point->y = (float)point->original_y * scale;
	point->z = (float)point->original_z * z_scale;
}

static void	translate(t_point *point, int x_move, int y_move)
{
	point->x_2d += x_move;
	point->y_2d += y_move;
}

static void	print_points_for_debug(t_fdf *fdf)
{
	int	x;
	int	y;

	printf("<<print_points_for_debug>>\n");
	printf("scale: %f, z_scale: %f, x_move: %d, y_move: %d\n",
			fdf->scale,
			fdf->scale / fdf->depth_scale,
			fdf->x_move,
			fdf->y_move);
	y = 0;
	printf("fdf.max_x: %d, fdf.max_y: %d\n", fdf->max_x, fdf->max_y);
	while (y < fdf->max_y)
	{
		x = 0;
		printf("<<point[%d]>>\n", y);
		while (x < fdf->max_x)
		{
			printf("point[%d][%d]: ", y, x);
			printf("y: %d, x: %d, z: %d, color: %X, is_exist: %d\n",
					fdf->points[y][x].original_y,
					fdf->points[y][x].original_x,
					fdf->points[y][x].original_z,
					fdf->points[y][x].color,
					fdf->points[y][x].is_exist);
			printf("y: %f, x: %f, z: %f x_2d: %d, y_2d: %d\n",
					fdf->points[y][x].y,
					fdf->points[y][x].x,
					fdf->points[y][x].z,
					fdf->points[y][x].x_2d,
					fdf->points[y][x].y_2d);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	transform(t_fdf *fdf, float scale, float z_scale, int x_move,
		int y_move)
{
	int	x;
	int	y;

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
	if (x == 0)
		print_points_for_debug(fdf);
}

/*
To rotate the figure:

At the beginning angle1 = angle2 = 0º,
	and to rotate the figure you only have to vary those angles.

    x (With angles) = x * cos(angle1) - y * sin(angle1)
    y (With angles) = x * sin(angle1) + y * cos(angle1) * cos(angle2) - z
	* sin(angle2)
    z (With angles) = y * sin(angle2) - z * cos(angle2)

Perspectives to convert in FDF:

    Isometric
        Xi = x * cos(30º) + y * sen(30º)
        Yi = x * sen(30º) + y * cos(30º) - z
    Cavalier
        Xc = (x - z * cos(45º)) - (y - z * sen(45º)) * cos(45º)
        Yc = y - z * sen(45º)
    Top view
        Xt = x
        Yt = y
    Frontal view
        Xf = x + y
        Yf = -z

 */
