/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:57:10 by sakitaha          #+#    #+#             */
/*   Updated: 2024/01/26 23:46:15 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Sets the z value of the point. Returns the endptr of the string.
 * Updates the max_z and min_z values of the fdf struct.
 */
static char	*set_point_num(t_fdf *fdf, t_point *point, char *str)
{
	long	num;
	char	*endptr;

	errno = 0;
	endptr = str;
	num = ft_strtol(str, &endptr, 10);
	if (errno != 0 || num < INT_MIN || INT_MAX < num)
	{
		return (NULL);
	}
	point->source_z = (int)num;
	point->z = (float)point->source_z;
	if (point->source_z > fdf->max_z)
	{
		fdf->max_z = point->source_z;
	}
	if (point->source_z < fdf->min_z)
	{
		fdf->min_z = point->source_z;
	}
	return (endptr);
}

/**
 * Checks if the current string is a valid endptr.
 */
static bool	is_valid_end(char *str)
{
	if (str[0] == '\0' || (str[0] == '\n' && str[1] == '\0'))
	{
		return (true);
	}
	return (false);
}

/**
 * Sets the rgb values of the point based on the given color.
 */
static void	set_rgb_color(t_point *point, unsigned int color)
{
	point->rgb[0] = (unsigned char)(color >> 16);
	point->rgb[1] = (unsigned char)(color >> 8);
	point->rgb[2] = (unsigned char)color;
}

/**
 * Sets the color of the point. Returns the endptr of the string.
 * Returns NULL if the color is invalid.
 */
static char	*set_point_color(t_point *point, char *str)
{
	char	*endptr;
	long	num;

	if (str[0] != ',' || str[1] != '0' || str[2] != 'x')
	{
		return (NULL);
	}
	str++;
	endptr = str;
	errno = 0;
	num = ft_strtol(str, &endptr, 16);
	if (errno != 0 || num < 0x000000 || 0xFFFFFF < num)
	{
		return (NULL);
	}
	point->color = (unsigned int)num;
	set_rgb_color(point, point->color);
	return (endptr);
}

/**
 * Parses the string and stores the result in the struct.
 * Returns false if an error occurs during the process.
 */
bool	parse_point(t_fdf *fdf, t_point *point, char *str)
{
	char	*endptr;

	endptr = set_point_num(fdf, point, str);
	if (!endptr)
	{
		return (false);
	}
	if (is_valid_end(endptr))
	{
		point->is_exist = true;
		return (true);
	}
	endptr = set_point_color(point, endptr);
	if (!endptr || !is_valid_end(endptr))
	{
		return (false);
	}
	point->is_exist = true;
	return (true);
}
