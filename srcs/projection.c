/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:43:23 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/19 21:10:27 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "fdf.h"
// #include <math.h>

// // 等角投影
// void	isometric_projection(t_point *point)
// {
// 	float	x;
// 	float	y;
// 	float	z;

// 	x = point->x;
// 	y = point->y;
// 	z = point->z;
// 	point->x = (x - y) * sqrt(2.0) / 2;
// 	point->y = ((x + y) * sqrt(2.0) - z * sqrt(6.0)) / 3;
// 	point->z = z;
// }

// // 正面投影 これいらないよね？
// void	orthographic_projection(t_point *point)
// {
// 	point->x = point->x;
// 	point->y = point->y;
// 	point->z = 0;
// }

// // 斜投影
// void	oblique_projection(t_point *point, float degrees)
// {
// 	float	x;
// 	float	y;
// 	float	z;
// 	float	radians;

// 	x = point->x;
// 	y = point->y;
// 	z = point->z;
// 	radians = degrees * M_PI / 180.0;
// 	point->x = x + z * cos(radians);
// 	point->y = y + z * sin(radians);
// 	point->z = 0;
// }

// // 透視投影
// void	perspective_projection(t_point *point)
// {
// 	float	x;
// 	float	y;
// 	float	z;

// 	x = point->x;
// 	y = point->y;
// 	z = point->z;
// 	// 徐算エラー防止
// 	if (z == 0)
// 		z = 1.0;
// 	point->x = x / z;
// 	point->y = y / z;
// 	point->z = z;
// }

// // x軸周りの回転
// void	rotate_x(t_point *point, float degrees)
// {
// 	float	x;
// 	float	y;
// 	float	z;
// 	float	radians;

// 	x = point->x;
// 	y = point->y;
// 	z = point->z;
// 	radians = degrees * M_PI / 180.0;
// 	point->x = x;
// 	point->y = y * cos(radians) - z * sin(radians);
// 	point->z = y * sin(radians) + z * cos(radians);
// }

// // y軸周りの回転
// void	rotate_y(t_point *point, float degrees)
// {
// 	float	x;
// 	float	y;
// 	float	z;
// 	float	radians;

// 	x = point->x;
// 	y = point->y;
// 	z = point->z;
// 	radians = degrees * M_PI / 180.0;
// 	point->x = x * cos(radians) + z * sin(radians);
// 	point->y = y;
// 	point->z = -x * sin(radians) + z * cos(radians);
// }

// // z軸周りの回転
// void	rotate_z(t_point *point, float degrees)
// {
// 	float	x;
// 	float	y;
// 	float	z;
// 	float	radians;

// 	x = point->x;
// 	y = point->y;
// 	z = point->z;
// 	radians = degrees * M_PI / 180.0;
// 	point->x = x * cos(radians) - y * sin(radians);
// 	point->y = x * sin(radians) + y * cos(radians);
// 	point->z = z;
// }

// #define ZOOM_IN_FACTOR 1.5
// #define ZOOM_OUT_FACTOR 0.5

// void	zoom_in(t_point *point)
// {
// 	point->x *= ZOOM_IN_FACTOR;
// 	point->y *= ZOOM_IN_FACTOR;
// 	point->z *= ZOOM_IN_FACTOR;
// }

// void	zoom_out(t_point *point)
// {
// 	point->x *= ZOOM_OUT_FACTOR;
// 	point->y *= ZOOM_OUT_FACTOR;
// 	point->z *= ZOOM_OUT_FACTOR;
// }
