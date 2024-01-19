/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:07 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/20 00:45:52 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_rgb_color(t_point *point, char *str)
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

static bool	is_valid_color(char *str)
{
	size_t	index;

	if (str[0] != ',' || str[1] != '0' || str[2] != 'x')
	{
		return (false);
	}
	str += 3;
	index = 0;
	while (index < 6)
	{
		if (!ft_isxdigit(str[index]))
		{
			return (false);
		}
		index++;
	}
	if (str[6] != '\0')
	{
		return (false);
	}
	return (true);
}

static void	set_default_color(t_point *point)
{
	point->rgb[0] = 255;
	point->rgb[1] = 255;
	point->rgb[2] = 255;
}

static void	set_point_values(t_fdf *fdf, size_t x, size_t y, int z)
{
	t_point	*point;

	point = &fdf->points[y][x];
	point->source_z = z;
	point->x = (float)x;
	point->y = (float)y;
	point->z = (float)point->source_z;
	if (point->source_z > fdf->max_z)
		fdf->max_z = point->source_z;
	if (point->source_z < fdf->min_z)
		fdf->min_z = point->source_z;
}

bool	parse_point_input(char *point_input, t_fdf *fdf, size_t x, size_t y)
{
	t_atoi_res	atoi_res;
	size_t		color_start_index;

	atoi_res = ft_atoi_endptr(point_input);
	if (atoi_res.is_valid == false)
	{
		return (false);
	}
	set_point_values(fdf, x, y, atoi_res.num);
	if (atoi_res.endptr[0] == '\0')
	{
		set_default_color(&fdf->points[y][x]);
		return (true);
	}
	if (!is_valid_color(atoi_res.endptr))
	{
		return (false);
	}
	set_rgb_color(&fdf->points[y][x], atoi_res.endptr + 3);
	return (true);
}
