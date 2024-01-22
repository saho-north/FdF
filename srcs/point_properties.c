/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_properties.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/20 15:10:18 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/20 15:44:50 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Sets the x y z values of the point.
 */
void	set_point_values(t_fdf *fdf, size_t x, size_t y, int z)
{
	t_point	*point;

	point = &fdf->points[y][x];
	point->source_z = z;
	if (point->source_z > fdf->max_z)
	{
		fdf->max_z = point->source_z;
	}
	if (point->source_z < fdf->min_z)
	{
		fdf->min_z = point->source_z;
	}
	point->x = (float)x;
	point->y = (float)y;
	point->z = (float)point->source_z;
}

/**
 * Sets the default color of the point.
 */
void	set_default_color(t_point *point)
{
	point->rgb[0] = 255;
	point->rgb[1] = 255;
	point->rgb[2] = 255;
}

/**
 * Sets the rgb values of the point.
 */
void	set_rgb_color(t_point *point, char *str)
{
	int		high_nibble;
	int		low_nibble;
	size_t	index;

	index = 0;
	while (index < 3 && str[index * 2] != '\0' && str[index * 2 + 1] != '\0')
	{
		high_nibble = ft_digittoint(str[index * 2]);
		low_nibble = ft_digittoint(str[index * 2 + 1]);
		point->rgb[index] = (unsigned char)(high_nibble * 16 + low_nibble);
		index++;
	}
}
