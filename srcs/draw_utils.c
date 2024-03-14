/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 23:36:03 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/14 23:41:30 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Put a pixel on the window.
 */
void	pixel_put(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addr + (y * fdf->stride + x * (fdf->bpp / 8));
	*(unsigned int *)dst = color;
}

/**
 * Check and put a pixel on the window if it's valid based on depth buffer.
 */
bool	is_valid_pixel(t_fdf *fdf, int x, int y, double z)
{
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
	{
		return (false);
	}
	if (fdf->depth_buffer[y][x] > z)
	{
		return (false);
	}
	fdf->depth_buffer[y][x] = z;
	return (true);
}

double	get_depth(t_line_draw_data *line_data, double t)
{
	return (ft_interpolate(line_data->start_z, line_data->end_z, t));
}

int	get_lerpcolor(t_line_draw_data *line_data, double t)
{
	return (ft_lerpcolor(line_data->color0, line_data->color1, t));
}
