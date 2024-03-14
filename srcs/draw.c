/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakitaha <sakitaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:41:59 by sakitaha          #+#    #+#             */
/*   Updated: 2024/03/14 23:43:24 by sakitaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	draw_steep(t_fdf *fdf, t_point *p, t_line_draw_data *line_data)
{
	int		err;
	int		x;
	int		y;
	int		i;
	double	t;

	err = 2 * line_data->abs_dx - line_data->abs_dy;
	x = p->x_2d;
	y = p->y_2d;
	i = 0;
	while (i++ <= line_data->abs_dy)
	{
		t = (double)i / line_data->abs_dy;
		if (is_valid_pixel(fdf, x, y, get_depth(line_data, t)))
			pixel_put(fdf, x, y, get_lerpcolor(line_data, t));
		err += 2 * line_data->abs_dx;
		if (err > 0)
		{
			x += line_data->x_direction;
			err -= 2 * line_data->abs_dy;
		}
		y += line_data->y_direction;
	}
}

static void	draw_shallow(t_fdf *fdf, t_point *p, t_line_draw_data *line_data)
{
	int	err;
	int	x;
	int	y;
	int	i;
	int	t;

	err = 2 * line_data->abs_dy - line_data->abs_dx;
	x = p->x_2d;
	y = p->y_2d;
	i = 0;
	while (i++ <= line_data->abs_dx)
	{
		t = (double)i / line_data->abs_dx;
		if (is_valid_pixel(fdf, x, y, get_depth(line_data, t)))
			pixel_put(fdf, x, y, get_lerpcolor(line_data, t));
		err += 2 * line_data->abs_dy;
		if (err > 0)
		{
			y += line_data->y_direction;
			err -= 2 * line_data->abs_dx;
		}
		x += line_data->x_direction;
	}
}

static void	set_line_data(t_fdf *fdf, t_line_draw_data *line_data, t_point *p0,
		t_point *p1)
{
	line_data->abs_dx = abs(p1->x_2d - p0->x_2d);
	line_data->abs_dy = abs(p1->y_2d - p0->y_2d);
	line_data->x_direction = 1;
	if (p1->x_2d < p0->x_2d)
	{
		line_data->x_direction = -1;
	}
	line_data->y_direction = 1;
	if (p1->y_2d < p0->y_2d)
	{
		line_data->y_direction = -1;
	}
	line_data->color0 = get_color(fdf, p0);
	line_data->color1 = get_color(fdf, p1);
	line_data->start_z = p0->z;
	line_data->end_z = p1->z;
}

static void	draw_line(t_fdf *fdf, t_point *p0, t_point *p1)
{
	t_line_draw_data	line_data;

	if (!p0->is_exist || !p1->is_exist || !liang_barsky(p0, p1))
	{
		return ;
	}
	set_line_data(fdf, &line_data, p0, p1);
	if (line_data.abs_dx > line_data.abs_dy)
	{
		draw_shallow(fdf, p0, &line_data);
	}
	else
	{
		draw_steep(fdf, p0, &line_data);
	}
}

void	draw_wireframe(t_fdf *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->max_y)
	{
		x = 0;
		while (x < fdf->max_x)
		{
			if (x + 1 < fdf->max_x)
			{
				draw_line(fdf, &fdf->points[y][x], &fdf->points[y][x + 1]);
			}
			if (y + 1 < fdf->max_y)
			{
				draw_line(fdf, &fdf->points[y][x], &fdf->points[y + 1][x]);
			}
			x++;
		}
		y++;
	}
}
