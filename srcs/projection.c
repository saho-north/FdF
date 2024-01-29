/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 14:43:23 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/24 23:09:18 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// 等角投影
void	isometric_projection(t_point *point)
{
	float	x;
	float	y;
	float	z;

	x = point->x;
	y = point->y;
	z = point->z;
	point->x = (x - y) * sqrt(2.0) / 2;
	point->y = ((x + y) * sqrt(2.0) - z * sqrt(6.0)) / 3;
	point->z = z;
}

void	isometric_projection(t_point *point)
{
	float	x;
	float	y;
	float	z;

	x = point->x;
	y = point->y;
	z = point->z;
	point->x = (x - y) * cos(30 * M_PI / 180);
	point->y = (x + y) * sin(30 * M_PI / 180) - z;
}
