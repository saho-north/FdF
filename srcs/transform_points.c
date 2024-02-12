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

void	set_initial_scale(t_fdf *fdf)
{
	float	x_len;
	float	y_len;

	x_len = ((float)WIN_WIDTH * 0.8) / (fdf->max_x - 1);
	y_len = ((float)WIN_HEIGHT * 0.8) / (fdf->max_y - 1);
	fdf->scale = fmin(x_len, y_len);
}

// TODO: check if the logic is correct
// how should I control over accumulated scaling later on
void	apply_scaling(t_fdf *fdf)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			if(fdf->points[y][x].is_exist == false)
			{
				break;
			}
			fdf->points[y][x].x += fdf->scale * x;
			fdf->points[y][x].y += fdf->scale * y;
			x++;
		}
		y++;
	}
}

// 何か違う気がする
void	prepare_initial_centering(t_fdf *fdf)
 {
	size_t	x;
	size_t	y;
	int		x_min = (int)((fdf->points[fdf->max_y - 1][0].x - fdf->points[fdf->max_y - 1][0].y) * cos(30 * M_PI / 180));
	int		x_max = (int)((fdf->points[0][fdf->max_x - 1].x - fdf->points[0][fdf->max_x - 1].y) * cos(30 * M_PI / 180));
	int		y_min = (int)((fdf->points[0][0].x - fdf->points[0][0].y) * sin(30 * M_PI / 180) - fdf->points[0][0].z);
	int		y_max = (int)((fdf->points[fdf->max_y - 1][fdf->max_x - 1].x - fdf->points[fdf->max_y - 1][fdf->max_x - 1].y) * sin(30 * M_PI / 180) - fdf->points[fdf->max_y - 1][fdf->max_x - 1].z);
	fdf->x_move = WIN_WIDTH / 2 - (x_max + x_min) / 2;
	fdf->y_move = WIN_HEIGHT / 2 - (y_max + y_min) / 2;
 }

 void	apply_move(t_fdf *fdf)
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
			fdf->points[y][x].x += fdf->x_move;
			fdf->points[y][x].y += fdf->y_move;
			x++;
		}
		y++;
	}
 }

 void	isometric_projection(t_point *point)
{
	point->x_2d = (point->x - point->y) * cos(30 * M_PI / 180);
	point->y_2d = (point->x + point->y) * sin(30 * M_PI / 180) - point->z;
}

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
			if(fdf->points[y][x].is_exist == false)
			{
				break;
			}
			isometric_projection(&fdf->points[y][x]);
			x++;
		}
		y++;
	}
}


/**
 * Transform the points (x, y, z) to the 2D plane.
 * Apply scale and movement during the process
 */
//  この順番が正しいのかわからない
void	transform_points(t_fdf *fdf)
{
	set_initial_scale(fdf);
	apply_scaling(fdf);
	prepare_initial_centering(fdf);
	apply_move(fdf);
	apply_isometric_projection(fdf);
}
